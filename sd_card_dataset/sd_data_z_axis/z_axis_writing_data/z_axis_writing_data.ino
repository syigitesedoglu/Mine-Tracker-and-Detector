#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <SD.h>

#define MPU6050_ADDR 0x68 // MPU6050's I2C address
#define PIN_SPI_CS 4      // Micro SD CARD Chip Select pin

MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!SD.begin(PIN_SPI_CS)) {
    Serial.println("SD CARD CANNOT WORK!");
    return;
  }
  Serial.println("SD CARD IS WORKING");
  mpu.setFullScaleAccelRange(2); // Set to ±2g
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Correction factor for ±2g
  float acc_factor = 9.81 / 16384;

  // Calculate the real acceleration value (m/s^2) and calibration part. 
  float acc_z = ((az * acc_factor) / 14.814) - 0.015;

  // Constrain the acceleration value to be within the range [0.64, 0.70] using if statements.
  if (acc_z < 0.67) {
    acc_z = 0.67;
  } else if (acc_z > 0.70) {
    acc_z = 0.70;
  }

  // Print the result in the serial monitor
  Serial.print("Acceleration Z: ");
  Serial.print(acc_z);
  Serial.println(" m/s^2");

  // Open the file to write
  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Acceleration: ");
    dataFile.println(acc_z); // Ensure you write the constrained value
    dataFile.close();
  } else {
    Serial.println("FILE CANNOT OPEN!");
  }

  delay(100); // after 100ms repeat the loop
}
