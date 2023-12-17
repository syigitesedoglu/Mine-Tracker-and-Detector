#include <NewPing.h>

// Define sensor pins
const int trigPin1 = 12;
const int echoPin1 = 13;
const int trigPin2 = 11;
const int echoPin2 = 10;

// Define maximum sensor range
const int maxDistance = 400; // cm

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
}

void loop() {
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
