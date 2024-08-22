# A PROTOTYPE IMPLEMENTATION OF IMU BASED POSITIONING SYSTEM FOR HAND-HELD DETECTORS

* Location-dependent data collection is crucial for some subsurface imaging detectors. The positioning information in question can be obtained based on image processing, Radio Frequency (RF), and Inertial Measurement Unit (IMU). In this study, IMU-based positioning system for Ground Penetrating Radar (GPR) sensor has been studied. Ultimate aim is to use this system for GPR based mine detectors.

* In order to obtain ground truth for acceleration values, IMU module was placed on a four-wheel mechanism and the acceleration data was obtained and registered by using the data coming from embedded encoders. In the next stage location calculation was carried out by using Kalman filter and then we made a comparison between ground truth data and Kalman filter estimation.
 
* Test setup contains a robotic system equipped with an L298N H-Bridge motor driver to control two DC motors,  MPU6050 IMU sensor is used for acceleration data collection and two Arduino systems: Arduino Nano and Uno to process signals. By taking the noise covariance into account, Kalman filter estimation performance was improved and acceleration estimation of  a=0.675 m/s2 was obtained within a range of 0.675±0.002.
 
* The results show that the acceleration estimation of the mechanism during 1-meter movement using the Kalman filter is obtained within a reasonable error range. In the final phase of the project, a precise real-time positioning system will be completed to accurately determine the position of the mine detector. This prototype system can serve as a reliable testbed for IMU-based positioning projects for undergraduate students.
