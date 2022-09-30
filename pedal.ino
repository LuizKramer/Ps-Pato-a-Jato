#include "Oled.h"

#include "DHT.h"
#include <DHT_U.h>

#define DHTPIN A1      // pino que estamos conectado
#define DHTTYPE DHT11  // DHT 11

#define potenciometerPin A0
#define motorPin 5


Oled oled;
int potMax = 105;
int potMin = 5;
float lastValue = 0;
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
 
  int dataPercent = map(potData, potMin, potMax, 0, 100);
  int dataFilter = map(potData, potMin, potMax, 0, 255);
  if(dataPercent > 100)
    dataPercent = 100; 
  if(dataPercent < 5)
    dataPercent = 0;
  float exponencial = pow(dataPercent, 1.505);
  Serial.println(dataFilter);
  if(dataFilter < 5)
    dataFilter = 0;
  else if(dataFilter > 255)
    dataFilter = 255;
  analogWrite(motorPin, dataFilter);

Serial.print("Pot: ");
Serial.println(potData);
  

  Serial.println(lastValue);

  oled.setDisplay(dataPercent, lastValue);
  float t = dht.readTemperature();

  if (!isnan(t)) {
    if(t < 0)
      t*= -1;
    lastValue = t;
  }

  
}