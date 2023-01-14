#include <QTRSensors.h>
const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;

const int analogPin0 = A0;
const int analogPin1 = A1;
const int analogPin2 = A2;
const int analogPin3 = A3;
const int analogPin4 = A4;
const int analogPin5 = A5;

int m1Speed = 0;
int m2Speed = 0;

unsigned long currentTime;
int rotationTime = 650;

// increase kp’s value and see what happens
float kp = 10;
float ki = 0;
float kd = 2;

int p = 0;
int i = 0.002;
int d = 0;

int error = 0;
int lastError = 0;

const int maxSpeed = 255;
const int minSpeed = -255;

const int baseSpeed = 225;

QTRSensors qtr;

int forwardTime = 300;
int checkForwardTime = 0; 
int forwardMovement = 150;
int restMotor = 0;
int isToRight = 0;
int lineCounter = 0;
int maximumCrosses = 5;
int  qtrPinA = 0;//analogRead(A0);
int  qtrPinB = 0;
int  qtrPinC = 0;
int  qtrPinD = 0;
int  qtrPinE = 0;
int  qtrPinF = 0;
int timeToRest = 100;

const byte rightDirection = 0;
const byte leftDirection = 1;
const int calibrationTh = 300;

const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = {0, 0, 0, 0, 0, 0};
void setup() {

  // pinMode setup
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorCount);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  
  currentTime = millis();
  // calibrate the sensor
  verifyDirection();
  calibration();
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
   
}

void moveLeft() {
  if (isToRight == rightDirection) {
    m1Speed = restMotor;
    m2Speed = -forwardMovement;
  }
}

void moveRight() {
  if (isToRight == leftDirection) {
    m1Speed = restMotor;
    m2Speed = forwardMovement;
  }
}

void readInput() {
  qtrPinA = analogRead(analogPin5);
  qtrPinB = analogRead(analogPin4);
  qtrPinC = analogRead(analogPin3);
  qtrPinD = analogRead(analogPin2);
  qtrPinE = analogRead(analogPin1);
  qtrPinF = analogRead(analogPin0);
}

void verifyDirection() {
  readInput();
  if ((qtrPinA > calibrationTh) && (qtrPinF < calibrationTh)) { //este in dreapta 
    isToRight = rightDirection;
  }

  if ((qtrPinF > calibrationTh) && (qtrPinA < calibrationTh)) { // este in stanga
    isToRight = leftDirection;
  }
}

unsigned long timer = 0;
const long time = 2500;

void calibration() {
  readInput();
  timer = millis();
  while (lineCounter < maximumCrosses) {
    if (millis() - timer > time)
      break;
    if(isToRight == rightDirection) { // initial e in dreapta si line counter = 0
      readInput();
      moveLeft();
    } 
    else {
      readInput();
      moveRight();
    }
    setMotorSpeed(m1Speed, m2Speed);
    verifyDirection();
    qtr.calibrate();
  }
}

const int maxSensorValue = 5000;
const int minSensorValue = 0;
const int maxMappingValue = 30;
const int minMappingValue = -30;
const int errorTh = 0;
const int bigAngleTh = 20;
const int lowKp = 10;
const int highKp = 17;
const int lowKd = 3.5;
const int highKd = 4;
const int adjustValue = 40;

void loop() { 
  int error = map(qtr.readLineBlack(sensorValues), minSensorValue, maxSensorValue, minMappingValue, maxMappingValue);

  int motorSpeed = kp * p + ki * i + kd * d; // = error in this case
  
  m1Speed = baseSpeed;
  m2Speed = baseSpeed;

  //adjustments for big angles
  if (error < errorTh) {
    m1Speed += motorSpeed;
  }
  else if (error > errorTh) {
    m2Speed -= motorSpeed;
  }

  if (error <= -1 * bigAngleTh) {
    m2Speed -= adjustValue;
  } else if (error >= bigAngleTh)
    m1Speed -= adjustValue;

  m1Speed = constrain(m1Speed, minSpeed, maxSpeed);
  m2Speed = constrain(m2Speed, minSpeed, maxSpeed);

  setMotorSpeed(m1Speed, m2Speed);

}

void pidControl(float kp, float ki, float kd) {
  p = error;
  i = i + error;
  d = error - lastError;
  lastError = error;

  if (error > bigAngleTh){
    kp = highKp;
    kd = highKd;
  }
  else { 
    kp = lowKp;
    kd = lowKd;
  }
}


// each arguments takes values between -255 and 255. The negative values represent the motor speed in reverse.
void setMotorSpeed(int motor1Speed, int motor2Speed) {
   motor1Speed = -motor1Speed;
   motor2Speed = -motor2Speed;
  if (motor1Speed == 0) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  }
  else {
    if (motor1Speed > 0) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == 0) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  }
  else {
    if (motor2Speed > 0) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    }
  }
}