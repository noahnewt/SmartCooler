#include <dht.h>
#include <LiquidCrystal.h>
#include <Servo.h>
Servo myServo;
dht DHT;
#define DHT11_PIN 7
LiquidCrystal lcd(12,11,5,4,3,2);
int trigPin = 10, echoPin = 13; 
int servo = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servo);
}

void displayLCD(float temp, float humid) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("F");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humid);
  lcd.print("%");
}

void displayDistance(int distance, int duration){
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" inch");
}

void loop() { 
  int duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // receiving the echo
  distance = (duration/2)/72;
  displayDistance(distance, duration);

  if(distance <= 10){
    myServo.write(-90);
    delay(5000);
    myServo.write(90);
  }

  int chk = DHT.read11(DHT11_PIN);
  float temp = DHT.temperature;
  float humid = DHT.humidity;
  temp = (temp * 1.8) + 32;
  displayLCD(temp, humid);
  delay(3000);
}
