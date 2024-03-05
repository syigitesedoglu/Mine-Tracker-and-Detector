int sensor = 12; //FC-33 Hız sensörünün data pini (Interrupt Pin, INT 0)
unsigned int rpm = 0; //Dakikadaki devir sayısı
float speed = 0; //Km/h
volatile byte counter = 0;
unsigned long timeold = 0;
unsigned int encoder = 20; //Encoder disk üzerindeki delik sayısı
const int wheel = 70; //Tekerleğin çapı 70 mm
static volatile unsigned long debounce=0; //Kapasite etkisinin kod ile çözümü için
int pwm = 10; //Enable sinyali hız kontrolü için

#define motorpin1a 2
#define motorpin1b 3
#define motorpin2a 4
#define motorpin2b 5


void setup(){
pinMode(sensor,INPUT); //FC-33 Hız sensörünün data pini giriş
attachInterrupt(digitalPinToInterrupt(sensor),counter,RISING); //Sinyalin yükselen kenarında sayma
counter=0;
rpm=0;
timeold=0;

//motor pinleri
pinMode(pwm,OUTPUT);
pinMode(motorpin1a, OUTPUT);
pinMode(motorpin1b, OUTPUT);
pinMode(motorpin2a, OUTPUT);
pinMode(motorpin2b, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
digitalWrite(encoder, HIGH);

Serial.begin(9600);
}

void loop(){
if (millis()-timeold>=1000){
noInterrupts();
rpm=(60*1000/encoder)/(millis()-timeold)*counter; //RPM’in hesaplanması
speed=rpm*3.1416*wheel*60/1000000; //Hızın hesaplanması
timeold=millis();
Serial.println("RPM = ");
Serial.println(rpm,DEC);
Serial.println("period/mn");
Serial.println("Speed=");
Serial.println(speed,2);
Serial.println("km/h");
counter=0;
interrupts();
  }
  if (digitalRead(sensor) && (micros()-debounce>500) && digitalRead(sensor)){ //500 mikro saniyelik kapasite etkisi
    debounce = micros();
    counter ++ ;
    Serial.println(counter);} //Sayma işlemi
    delay(100);

    analogWrite(9, 100); //ENA   pin
    analogWrite(10, 80); //ENB pin

    digitalWrite(motorpin1a,   LOW);
    digitalWrite(motorpin1b, HIGH);

    digitalWrite(motorpin2a, HIGH);
    digitalWrite(motorpin2b, LOW);
    delay(100);
}
