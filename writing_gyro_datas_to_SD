#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <MPU6050.h>

#define MPU6050_ADDR 0x68 // MPU6050'nin I2C adresi
#define SD_CS_PIN 10       // Micro SD kartın Chip Select pini

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  
  // MPU6050'yi başlat
  Wire.begin();
  mpu.initialize();
  
  // SD kartı başlat
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD kart başlatılamadı!");
    return;
  }
  
  Serial.println("SD kart başlatıldı");
}

void loop() {
  // Verileri oku
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Verileri seri monitöre yazdır
  Serial.print("Acceleration: ");
  Serial.print(ax);
  Serial.print(", ");
  Serial.print(ay);
  Serial.print(", ");
  Serial.println(az);

  Serial.print("Gyro: ");
  Serial.print(gx);
  Serial.print(", ");
  Serial.print(gy);
  Serial.print(", ");
  Serial.println(gz);

  // Verileri SD karta yaz
  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Acceleration: ");
    dataFile.print(ax);
    dataFile.print(", ");
    dataFile.print(ay);
    dataFile.print(", ");
    dataFile.println(az);

    dataFile.print("Gyro: ");
    dataFile.print(gx);
    dataFile.print(", ");
    dataFile.print(gy);
    dataFile.print(", ");
    dataFile.println(gz);

    dataFile.close();
  } else {
    Serial.println("Dosya açılamadı!");
  }

  delay(1000); // 1 saniye bekle
}
