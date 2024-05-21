#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <SD.h>

#define MPU6050_ADDR 0x68 // MPU6050s I2C address
#define PIN_SPI_CS 4       // Micro SD CARD Chip Select pin

MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if(!SD.begin(PIN_SPI_CS)){
    Serial.println("SD CARD CANNOT WORK!");
    return;
  }
  Serial.println("SD CARD IS WORKING");
  mpu.setFullScaleAccelRange(8); //for ±8g
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  // Düzeltme faktörü (kullanılan ivme aralığına bağlı olarak)
  float acc_factor = 9.81 / 4096; // ±8g için
  
  // Calculate the real acceleration value (m/s^2)
  float acc_z = az * acc_factor;

  if(acc_z >=45.80){
    acc_z = 45.70;
  {
    
  
  // Print the result in serial monitor
  Serial.print("Acceleration Z: ");
  Serial.print(acc_z);
  Serial.println(" m/s^2");

  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Acceleration: ");
    dataFile.println(acc_z);

    dataFile.close();
  } else {
    Serial.println("FILE CANNOT OPEN!");
  }
  
  delay(100); // after the 100ms repeat the loop
}
