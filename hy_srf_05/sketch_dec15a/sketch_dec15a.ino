long duration;
    float distance;
    
    const int trig = 13;
    const int echo = 12;
   
    
    void setup() {
    pinMode(trig, OUTPUT); // Sets the trigPin as an Output
    pinMode(echo, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication
    }
    void loop() {
       distance = calculateDistance();
Serial.println(distance); 

    }
    float calculateDistance(){ 
  
  digitalWrite(trig, LOW); 
  delay(200);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH); 
  delay(1000);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
