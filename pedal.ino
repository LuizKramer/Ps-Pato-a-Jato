#include "Oled.h"

#include "DHT.h"
 
#define DHTPIN 15 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

#define potenciometerPin 4
#define motorPin 16

Oled oled;

DHT dht(DHTPIN, DHTTYPE);

int potData;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(potenciometerPin, INPUT);
  pinMode(motorPin, OUTPUT);
  oled.begin();
  
  
}



void loop() {
  // put your main code here, to run repeatedly:
  potData = analogRead(potenciometerPin);
  Serial.println(potData);
  Serial.println(dht.readTemperature());
  int dataFilter = map(potData, 0, 4095, 0, 255);
  analogWrite(motorPin, dataFilter);
  int dataPercent = map(potData, 0, 4095, 0, 100);
   float t = dht.readTemperature();
   if (isnan(t)) 
  {
    Serial.println("Failed to read from DHT");
     oled.setDisplay(dataPercent, -1);
  } 
  else
     oled.setDisplay(dataPercent, t);
  delay(100);
}
