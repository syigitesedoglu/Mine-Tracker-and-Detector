long duration;
    int distance;
    
    const int trig = 13;
    const int echo = 12;
   
    
    void setup() {
    pinMode(trig, OUTPUT); // Sets the trigPin as an Output
    pinMode(echo, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication
    }
    void loop() {
      int distance = calculateDistance(); // Replace with your sensor reading function

if (distance < 5) {
  // Object is very close! Take immediate action.
  Serial.println(distance);
  Serial.println("Object detected! Very close (less than 2 cm).");
  // Your immediate action code here (e.g., activate alarm, stop motor)
} else if (distance >= 5 && distance <= 10) {
  // Object is close. Take caution.
  Serial.println(distance);
  Serial.println("Object detected! Close (2 cm to 10 cm)."); 
  // Your cautionary action code here (e.g., slow down, sound warning)
} else if (distance > 10 && distance <= 50) {
  // Object is within moderate range. Be aware.
  Serial.println(distance);
  Serial.println("Object detected! Moderate range (10 cm to 50 cm).");
  // Your moderate awareness code here (e.g., display distance, change LED color)
} else if (distance > 50 && distance <= 100) {
  // Object is farther away. Monitor the situation.
  Serial.println(distance);
  Serial.println("Object detected! Farther range (50 cm to 100 cm)."); 
  // Your monitoring code here (e.g., log distance, update status)
} else if (distance > 100 && distance <= 150) {
  // Object is at the edge of the detection range.
  Serial.println(distance);
  Serial.println("Object detected! Edge of range (100 cm to 150 cm).");
  // Your edge-of-range code here (e.g., prepare for potential close encounter)
} else {
  // No object detected within the sensor range.
  Serial.println("No object detected.");
}

    }
    int calculateDistance(){ 
  
  digitalWrite(trig, LOW); 
  delay(200);
  digitalWrite(trig, HIGH); 
  delay(1000);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
