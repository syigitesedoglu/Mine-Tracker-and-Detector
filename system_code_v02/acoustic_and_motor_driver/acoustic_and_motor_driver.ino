#include <NewPing.h>

// Define sensor pins
int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5; 

// Define sensor pins
const int trigPin1 = 12;
const int echoPin1 = 13;
const int trigPin2 = 11;
const int echoPin2 = 10;

// Define maximum sensor range
const int maxDistance = 40; // cm

// Create NewPing objects for each sensor
NewPing sonar1(trigPin1, echoPin1, maxDistance);
NewPing sonar2(trigPin2, echoPin2, maxDistance);

void setup() {
  Serial.begin(9600);

  // Set trigger pins as outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);

  // Set echo pins as inputs
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);

  // Set the motorpins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,   OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(9,   OUTPUT); 
  pinMode(10, OUTPUT);
  //(Optional)
}

void loop() {
  
  analogWrite(9, 100); //ENA   pin
  analogWrite(10, 200); //ENB pin
  //(Optional)
  
  digitalWrite(motor1pin1,   HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
   digitalWrite(motor2pin2, LOW);
  delay(3000);

//  digitalWrite(motor1pin1,   LOW);
//  digitalWrite(motor1pin2, HIGH);
//
//  digitalWrite(motor2pin1, LOW);
//   digitalWrite(motor2pin2, HIGH);
//  delay(3000);
  // Measure distance from sensor 1
  unsigned int distance1 = sonar1.ping_cm();

  // Measure distance from sensor 2
  unsigned int distance2 = sonar2.ping_cm();

  // Print measured distances
  Serial.print("Sensor 1 Distance: ");
  Serial.print(distance1);
  Serial.print(" cm");
  Serial.print("\tSensor 2 Distance: ");
  Serial.println(distance2);
  Serial.println("-------");

  // Add your custom logic here based on measured distances...

  // Delay between measurements
  delay(100);
}
