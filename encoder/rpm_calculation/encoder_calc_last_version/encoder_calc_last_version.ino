#include "TimerOne.h"

const byte MOTOR1 = 2;
const byte MOTOR2 = 3;
volatile unsigned int counter1 = 0;
volatile unsigned int counter2 = 0;
const float diskslots = 20.0;
volatile float revolution1, revolution2;
unsigned long timeold = 0; // Initialize timeold

const float wheeldiameter = 7.00; // Changed to float

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
  Serial.println("Elapsed time: ");
  Serial.print(elapsedTime*1.28205128);
  
  float rps1 = (counter1 /60)/ (elapsedTime*1.28205128);
  float rps2 = (counter2 /60)/ (elapsedTime*1.28205128);
  Serial.print("Motor 1 RPS: ");
  Serial.println(rps1);
  Serial.print("Motor 2 RPS: ");
  Serial.println(rps2);
  
  float distance1 = rps1 * (3.14159 * wheeldiameter);
  float distance2 = rps2 * (3.14159 * wheeldiameter);
  Serial.print("Motor 1 Distance: ");
  Serial.println(distance1/100);
  Serial.print("Motor 2 Distance: ");
  Serial.println(distance2/100);

  
  float velocity1 = (distance1) / (elapsedTime*1.28205128); // Calculate velocity
  float velocity2 = (distance2) / (elapsedTime*1.28205128);
  prev_distance1 = distance1; // Update previous distance for next iteration
  prev_distance2 = distance2;
  Serial.print("Motor 1 Velocity: ");
  Serial.println(velocity1/100);
  Serial.print("Motor 2 Velocity: ");
  Serial.println(velocity2/100);

  float acceleration1 = (velocity1 - revolution1) / (elapsedTime*1.28205128); // Calculate acceleration
  float acceleration2 = (velocity2 - revolution2) / (elapsedTime*1.28205128);
  revolution1 = velocity1; // Update revolutions for next iteration
  revolution2 = velocity2;
  Serial.print("Motor 1 Acceleration: ");
  Serial.println(acceleration1);
  Serial.print("Motor 2 Acceleration: ");
  Serial.println(acceleration2);
  
  Serial.print(" \n");
  
  counter1 = 0;
  counter2 = 0;
  Timer1.attachInterrupt(ISR_timerone);
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
  analogWrite(5, 101.5);
  analogWrite(11, 100);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  delay(3000);
}
