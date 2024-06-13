#include "TimerOne.h"

const byte MOTOR1 = 2;
const byte MOTOR2 = 3;
volatile unsigned int counter1 = 0;
volatile unsigned int counter2 = 0;
const float diskslots = 20.0;
volatile float revolution1, revolution2;
unsigned long timeold = 0; // Initialize timeold

const float wheelDiameterCM = 7.0; // Measured wheel diameter in centimeters (assuming you measured in cm)

int enA = 11;
int in1 = 9;
int in2 = 8;

int enB = 5;
int in3 = 7;
int in4 = 6;

float prev_distance1 = 0; // Previous distance for motor 1
float prev_distance2 = 0; // Previous distance for motor 2

bool isForward = true; // Variable to track the direction

void ISR_count1()  
{
  counter1++;
} 

void ISR_count2()  
{
  counter2++;
} 

void ISR_timerone()
{
  Timer1.detachInterrupt();
  float rotation1 = counter1 / diskslots;
  float rotation2 = counter2 / diskslots;
  Serial.print("Motor Speed 1: ");
  Serial.print(rotation1);
  Serial.println(" revolutions/s");
  Serial.print("Motor Speed 2: ");
  Serial.print(rotation2);
  Serial.println(" revolutions/s");
  float elapsedTime = (millis() - timeold) / 1000.0; // Calculate elapsed time in seconds
  timeold = millis(); // Update timeold
  Serial.print("Elapsed time: ");
  Serial.println(elapsedTime * 1.38888889);
  
  float rps1 = (counter1 / 60) / (elapsedTime * 1.38888889);
  float rps2 = (counter2 / 60) / (elapsedTime * 1.38888889);
  Serial.print("Motor 1 RPS: ");
  Serial.println(rps1);
  Serial.print("Motor 2 RPS: ");
  Serial.println(rps2);
  
  float distance1, distance2; // Declare distance variables
  float distanceFactor = wheelDiameterCM / 100.0; // Convert diameter cm to meters

  if (isForward) { // If the direction is forward
    distance1 = (rps1 * 3.14159 * distanceFactor * elapsedTime * 1.38888889)*4.40; // Calculate forward distance
    distance2 = (rps2 * 3.14159 * distanceFactor * elapsedTime * 1.38888889)*4.40;
    Serial.println("Motor 1 Direction: Forward");
    Serial.println("Motor 2 Direction: Forward");
  } else { // If the direction is backward
    distance1 = (-rps1 * 3.14159 * distanceFactor * elapsedTime * 1.38888889)*4.40; // Calculate backward distance
    distance2 = (-rps2 * 3.14159 * distanceFactor * elapsedTime * 1.38888889)*4.40;
    Serial.println("Motor 1 Direction: Backward");
    Serial.println("Motor 2 Direction: Backward");
  }


Serial.print("Motor 1 Distance: ");
Serial.println(distance1); // Divided by 100 to convert to meters
Serial.print("Motor 2 Distance: ");
Serial.println(distance2); // Divided by 100 to convert to meters


  float velocity1, velocity2; // Declare velocity variables

 if (isForward) { // If the direction is forward
    velocity1 = distance1 / elapsedTime; // Calculate forward velocity
    velocity2 = distance2 / elapsedTime;
  } else { // If the direction is backward
    velocity1 = -(distance1 / elapsedTime); // Calculate backward velocity
    velocity2 = -(distance2 / elapsedTime);
  }

  prev_distance1 = distance1; // Update previous distance for next iteration
  prev_distance2 = distance2;
  Serial.print("Motor 1 Velocity: ");
  Serial.println(velocity1);
  Serial.print("Motor 2 Velocity: ");
  Serial.println(velocity2);

  float acceleration1 = (velocity1 - revolution1) / (elapsedTime * 1.38888889); // Calculate acceleration
  float acceleration2 = (velocity2 - revolution2) / (elapsedTime * 1.38888889);
  velocity1 = revolution1;
  velocity2 = revolution2;
  Serial.print("Motor 1 Acceleration: ");
  Serial.println((acceleration1*10)/20);
  Serial.print("Motor 2 Acceleration: ");
  Serial.println((acceleration2*10)/20);
  
  Serial.print("\n");
  
  
//  float acceleration1 = (velocity1 - 100.0) / (elapsedTime * 1.38888889); // Calculate acceleration
//  float acceleration2 = (velocity2 - 100.0) / (elapsedTime * 1.38888889);
//  revolution1 = velocity1; // Update revolutions for next iteration
//  revolution2 = velocity2;
//  Serial.print("Motor 1 Acceleration: ");
//  Serial.println(acceleration1);
//  Serial.print("Motor 2 Acceleration: ");
//  Serial.println(acceleration2);
//  
//  Serial.print("\n");

//   float acceleration1, acceleration2; // Declare acceleration variables
//
//  if (isForward) { // If the direction is forward
//    acceleration1 = (velocity1 - revolution1) / (elapsedTime * 1.28205128); // Calculate forward acceleration
//    acceleration2 = (velocity2 - revolution2) / (elapsedTime * 1.28205128);
//  } else { // If the direction is backward
//    acceleration1 = (velocity1 - revolution1) / (elapsedTime * 1.28205128); // Calculate backward acceleration
//    acceleration2 = (velocity2 - revolution2) / (elapsedTime * 1.28205128);
//  }
//
//  revolution1 = velocity1; // Update revolutions for next iteration
//  revolution2 = velocity2;
//  Serial.print("Motor 1 Acceleration: ");
//  Serial.println(acceleration1);
//  Serial.print("Motor 2 Acceleration: ");
//  Serial.println(acceleration2);
//  
//  Serial.print("\n");


//  if (!isForward) { // If the direction is not forward
//    Serial.println("Motor 1 Direction: Backward");
//    Serial.println("Motor 2 Direction: Backward");
//  }
  
  counter1 = 0;
  counter2 = 0;
  Timer1.attachInterrupt(ISR_timerone);
//  delay(1000);
}

void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(1000000);
  attachInterrupt(digitalPinToInterrupt(MOTOR1), ISR_count1, RISING);
  attachInterrupt(digitalPinToInterrupt(MOTOR2), ISR_count2, RISING);
  Timer1.attachInterrupt(ISR_timerone);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  timeold = millis();
} 

void loop()
{
  // Moving Forward
  analogWrite(5, 91.5);
  analogWrite(11, 90);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  delay(2000);
  

  // Stop the motor
  analogWrite(5, 0);
  analogWrite(11, 0);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  delay(1000);
  
  isForward = false; // Set the direction as backward
  Serial.println("Motor 1 Direction: Backward");
  Serial.println("Motor 2 Direction: Backward");
  Serial.println();
  
    // Moving backward
  analogWrite(5, 90);
  analogWrite(11, 90);
  digitalWrite(in1, HIGH);
  digitalWrite(in4, HIGH);
  delay(2000);
  isForward = true; // Set the direction as forward
  Serial.println("Motor 1 Direction: Forward");
  Serial.println("Motor 2 Direction: Forward");
  Serial.println();

  // Stop the motor
  analogWrite(5, 0);
  analogWrite(11, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in4, LOW);
  delay(1000);
  
}
