#include <Wire.h>
#include <MPU6050.h>

#define MPU6050_ADDR 0x68 // MPU6050'nin I2C adresi

MPU6050 mpu;

float angleX = 0; // X eksenindeki açı
float angleY = 0; // Y eksenindeki açı

float gyroX = 0; // X eksenindeki açısal hız
float gyroY = 0; // Y eksenindeki açısal hız

unsigned long lastTime;
float elapsedTime;

void setup() {
  Serial.begin(9600);
  
  // MPU6050'yi başlat
  Wire.begin();
  mpu.initialize();
  
  lastTime = micros();
}

void loop() {
  // Zamanı hesapla
  unsigned long now = micros();
  elapsedTime = (now - lastTime) / 1000000.0;
  lastTime = now;

  // Verileri oku
  int16_t gx, gy, gz;
  mpu.getRotation(&gx, &gy, &gz);
  
  // Açısal hızları hesapla
  gyroX = gx / 131.0; // Dönüş hızını elde etmek için ölçek faktörü kullanılır
  gyroY = gy / 131.0;

  // Açıları hesapla
  angleX += gyroX * elapsedTime;
  angleY += gyroY * elapsedTime;

  // Sonuçları seri monitöre yazdır
  Serial.print("X Angle: ");
  Serial.println(angleX);
  Serial.print("Y Angle: ");
  Serial.println(angleY);
  
  delay(20); // Örnekleme zamanı
}
