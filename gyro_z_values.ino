#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  
  // Ayarlanabilir hız değeri (±2g için 16384, ±4g için 8192, ±8g için 4096, ±16g için 2048)
  mpu.setFullScaleAccelRange(8); // ±8g ivme aralığını kullan
}

void loop() {
  // Z eksenindeki ivme değerini oku
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  
  // Düzeltme faktörü (kullanılan ivme aralığına bağlı olarak)
  float acc_factor = 9.81 / 4096; // ±8g için
  
  // Gerçek ivme değerini hesapla (m/s^2 cinsinden)
  float acc_z = az * acc_factor;
  
  // Sonucu seri monitöre yazdır
  Serial.print("Ivme Z: ");
  Serial.print(acc_z);
  Serial.println(" m/s^2");
  
  delay(100); // 100ms bekleyerek döngüyü tekrarla
}
