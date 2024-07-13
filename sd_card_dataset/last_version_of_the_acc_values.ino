#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <SD.h>

#define PIN_SPI_CS 4
MPU6050 mpu;

int direction = 1; // Initially forward direction (+1)

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize the MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
  // Initialize the SD card
  if (!SD.begin(PIN_SPI_CS)) {
    Serial.println("SD card initialization failed");
    return;
  }
  Serial.println("SD card can work correctly");
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  // Correction factor (depending on the used acceleration range)
  float acc_factor = 9.81 / 16384; // for ±2g
  
  // Calculate the real acceleration value (m/s^2)
  float acc_z = ((az * acc_factor) / 14.814) - 0.015;

  static unsigned long lastSwitchTime = 0;
  unsigned long currentTime = millis();

  // Change direction every 2 seconds
  if (currentTime - lastSwitchTime >= 2000) {  // 2000 ms = 2 seconds
    direction = -direction;  // Change direction (+1 <-> -1)
    lastSwitchTime = currentTime;  // Update the last direction change time
  }

  // Update acc_z value according to the direction change
  float adjusted_acc_z = acc_z * direction;

  // Print the adjusted acceleration value
  Serial.print("Acceleration Z: ");
  Serial.print(adjusted_acc_z);
  Serial.println(" m/s^2");

  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Acceleration: ");
    dataFile.println(adjusted_acc_z);

    dataFile.close();
  } else {
    Serial.println("FILE CANNOT OPEN!");
  }
  
  delay(100); // after 100ms repeat the loop
}
