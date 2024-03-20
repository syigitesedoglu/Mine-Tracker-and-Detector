#include "TimerOne.h"
//MOTOR 2 SAĞ
//MOTOR 1 SOL
// Constants for Interrupt Pins
// Change values if not using Arduino Uno
 
const byte MOTOR1 = 2;  // Motor 1 Interrupt Pin - INT 0
const byte MOTOR2 = 3;  // Motor 2 Interrupt Pin - INT 1
 
// Integers for pulse counters
unsigned int counter1 = 0;
unsigned int counter2 = 0;
// Motor A
 
int enA = 11;
int in1 = 9;
int in2 = 8;
 
// Motor B
 
int enB = 5;
int in3 = 7;
int in4 = 6;
// Float for number of slots in encoder disk
float diskslots = 20;  // Change to match value of encoder disk
const int wheeldiameter = 68.00;
volatile float rpm;
// Interrupt Service Routines
 
// Motor 1 pulse count ISR
void ISR_count1()  
{
  counter1++;  // increment Motor 1 counter value
} 
 
// Motor 2 pulse count ISR
void ISR_count2()  
{
  counter2++;  // increment Motor 2 counter value
} 

void rpm_calc()
{
  rpm++;
}

// TimerOne ISR
void ISR_timerone()
{
  Timer1.detachInterrupt();  // Stop the timer
  Serial.print("Motor Speed 1: "); 
  float rotation1 = (counter1 / diskslots) * 60.00;  // calculate RPM for Motor 1
  Serial.print(rotation1);  
  Serial.print(" RPM - "); 
  counter1 = 0;  //  reset counter to zero
  Serial.print("Motor Speed 2: "); 
  float rotation2 = (counter2 / diskslots) * 60.00;  // calculate RPM for Motor 2
  Serial.print(rotation2);  
  Serial.println(" RPM"); 
  counter2 = 0;  //  reset counter to zero
  int velocity = 3.14159*(wheeldiameter/100)*(rpm/60.0); // speed in m/s
  Serial.print(rpm);
  Serial.println("Velocity");
  rpm = 0; // reset rpm to zero
  
  Timer1.attachInterrupt( ISR_timerone );  // Enable the timer
  
}
 
void setup() 
{
  Serial.begin(9600);
  
  Timer1.initialize(1000000); // set timer for 1sec
  attachInterrupt(digitalPinToInterrupt (MOTOR1), ISR_count1, RISING);  // Increase counter 1 when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR2), ISR_count2, RISING);  // Increase counter 2 when speed sensor pin goes High
  Timer1.attachInterrupt( ISR_timerone ); // Enable the timer
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
} 
 
void loop()
{
  // Put whatever you want here!
  analogWrite(5, 68);//ENA   pin SAĞ
  analogWrite(11, 108); //ENB pin SOL
//  //(Optional)

  //digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  //digitalWrite(in4, LOW);
  delay(3000);
  // Nothing in the loop!
  // You can place code here
}
