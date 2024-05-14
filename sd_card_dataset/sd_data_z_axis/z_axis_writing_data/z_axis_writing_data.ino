#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <SD.h>

#define MPU6050_ADDR 0x68 // MPU6050'nin I2C adresi
#define PIN_SPI_CS 4       // Micro SD kartın Chip Select pini

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
  mpu.setFullScaleAccelRange(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  // Düzeltme faktörü (kullanılan ivme aralığına bağlı olarak)
  float acc_factor = 9.81 / 4096; // ±8g için
  
  // Gerçek ivme değerini hesapla (m/s^2 cinsinden)
  float acc_z = az * acc_factor;
  
  // Sonucu seri monitöre yazdır
  Serial.print("Acceleration Z: ");
  Serial.print(acc_z);
  Serial.println(" m/s^2");

  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Acceleration: ");
    dataFile.println(az);

    dataFile.close();
  } else {
    Serial.println("Dosya açılamadı!");
  }
  
  delay(100); // 100ms bekleyerek döngüyü tekrarla
}
