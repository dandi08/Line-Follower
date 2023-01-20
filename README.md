# Line-Follower

The Link of the video: https://drive.google.com/file/d/1C6JqfFnhgc2-JcmaQ20pVZuEGashmn9O/view?usp=sharing

# LedMatrixGame
<details closed>
<summary>Task requirements and objective 🏗️</summary>
<br>
  In teams consisting of two students, build a line follower using an arduino and other necessary components such as wheels, breadboard, wires, etc... accordingly. The task of the robot will be to follow a continuous black spline.
  In order to obtain the highest mark the robot should calibrate itself when placed over the line and then complete the track in under 20 seconds.
</details>

<details close>
<summary>Implementation 🧑‍💻️</summary>
<br>
  For this homework our teacher organised a 12 hours hackaton at our university. We built the robot prior to the hackaton. To build the robot we used a deafult line follower kit and an Arduino Uno. 
  
  The bigger challege for us was to program the robot. First, we tried to program the robot to do the first task: self-calibrate when the robot is placed over the black line. We tried to do this by giving power to both motors but in opposite directions so that the robot doesn't really move but rather rotates over the line, but since the motors were not perfect nor having same power we couldn't make it work despite trying to give different values to each one. After losing quite some time on this idea we decided that we should split the taks and instead of both of us working on same thing, one should start programming the robot to follow the line and other to do the self-calibrate. Working like this proved to be very efficient and we managed to do a pretty good job in the end. In terms of self-calibrating instead of using just motor power we used the sensors to detect if the robot passed over the black strip with all the sesors and should turn in the other direction.
  
  On the other hand, for the line following we used PID in order to program the robot starting from a simple code that "kind of" followed the line. In the initial code, motors were receiving power in the range of -50:50 multiplied with PID accordingly. First we shrinked the inveral to -30:30 and raised the P(Proportional) value. After we tought that we have a pretty good value of P we started to try values for D(Derivative) as well in order to make the robot return faster to the line and not wobble after a turn. In terms of the last variable, Integral, we tried to use it with some small values but it did not seem to help. After we found some good values for P and D we started to increase the speed and fine tune the parameters in the meantime accordigly.
  
  In terms of results we had our best time during a practice session: 19:40 seconds. After that we tried to add some changes to our parameters that were supposed to improve the time but unfortunately our fastest lap during official run was 21:00 seconds which is still a good time. For both of us this heackaton was really fun and interesting, we developed our communication and teamwork skills as well as our knowledge. Props to our teacher and TAs for this idea and since it was our last we want to thank them for this great, fun and interesting course!
  
</details>

<details close>
<summary>Showcase 📸️</summary>
<br>
Setup photos:
<div style="display: flex;">
  <img src="https://user-images.githubusercontent.com/63961737/213796320-2627d1c3-d355-404c-9453-bf70299747c0.jpeg" width="200">
  <img src="https://user-images.githubusercontent.com/63961737/213797273-5886c48c-5149-44ba-9dc9-f26484e6fd3f.jpeg" width="200">
</div>

Video link: https://drive.google.com/file/d/1u10tr5Iw1ubGaUx9A8igSYLICWKHucXJ/view?usp=share_link
</details>
