#include "TimerOne.h"

const byte MOTOR1 = 2;
const byte MOTOR2 = 3;
volatile unsigned int counter1 = 0;
volatile unsigned int counter2 = 0;
const float diskslots = 20.0;
volatile float revolution1, revolution2;
unsigned long timeold = 0; // Initialize timeold

const float wheelDiameterCM = 7.0; // Measured wheel diameter in centimeters (assuming you measured in cm)
bool isForward = true; // Variable to track the direction

int enA = 11;
int in1 = 9;
int in2 = 8;

int enB = 5;
int in3 = 7;
int in4 = 6;

float prev_distance1 = 0; // Previous distance for motor 1
float prev_distance2 = 0; // Previous distance for motor 2


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
    distance1 = (rps1 * 3.14159 * distanceFactor)*4.32; // Calculate forward distance
    distance2 = (rps2 * 3.14159 * distanceFactor)*4.32;
    Serial.println("Motor 1 Direction: Forward");
    Serial.println("Motor 2 Direction: Forward");
  } else { // If the direction is backward
    distance1 = (-rps1 * 3.14159 * distanceFactor)*4.32; // Calculate backward distance
    distance2 = (-rps2 * 3.14159 * distanceFactor)*4.32;
    Serial.println("Motor 1 Direction: Backward");
    Serial.println("Motor 2 Direction: Backward");
  }

  Serial.print("Motor 1 Distance: ");
  Serial.println(distance1); // Divided by 100 to convert to meters
  Serial.print("Motor 2 Distance: ");
  Serial.println(distance2); // Divided by 100 to convert to meters

  float velocity1, velocity2; // Declare velocity variables

  if (isForward) { // If the direction is forward
    velocity1 = distance1 / (elapsedTime * 1.38888889); // Calculate forward velocity
    velocity2 = distance2 / (elapsedTime * 1.38888889);
  } else { // If the direction is backward
    velocity1 = -distance1 / (elapsedTime * 1.38888889); // Calculate backward velocity
    velocity2 = -distance2 / (elapsedTime * 1.38888889);
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
  Serial.println(acceleration1*100);
  Serial.print("Motor 2 Acceleration: ");
  Serial.println(acceleration2*100);
  
  Serial.print("\n");
  
  counter1 = 0;
  counter2 = 0;
  Timer1.attachInterrupt(ISR_timerone);
}

void moveMotorForward(float distance) {
  // Moving Forward
  isForward = true;
  analogWrite(5, 101.5);
  analogWrite(11, 98);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  delay(1000 * distance / 0.009); // Move forward for calculated duration based on distance
  Serial.println("Motor1 direction is FORWARD!");
  Serial.println("Motor2 direction is FORWARD!");
  Serial.println();
}

void moveMotorBackward(float distance) {
  // Moving backward
  isForward = false;
  analogWrite(5, 101.5);
  analogWrite(11, 98);
  digitalWrite(in1, HIGH);
  digitalWrite(in4, HIGH);
  delay(1000 * distance / 0.009); // Move backward for calculated duration based on distance
  Serial.println("Motor1 direction is BACKWARD!");
  Serial.println("Motor2 direction is BACKWARD!");
  Serial.println();
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


