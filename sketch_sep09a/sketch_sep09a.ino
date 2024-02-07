#include <dht.h>
#include "HX711.h"
dht DHT11;

#define dPIN 5
#define calibration_factor -7050.0
#define DOUT 3
#define CLK 2

HX711 scale(DOUT, CLK);

int relayPin=7;

void setup() {
 Serial.begin(9600);
 Serial.println("Type, \tHumidity(%), \tTemperature(C), \tWeight");
 scale.set_scale(calibration_factor);
 scale.tare();
 pinMode(relayPin, OUTPUT);

}

void loop() {
  Serial.print("DHT11, \t");
  int chk=DHT11.read11(dPIN);
  Serial.print(DHT11.humidity, 1);
  Serial.print(", \t");
  Serial.print(DHT11.temperature, 1);
  Serial.print(", \t");
  Serial.print(scale.get_units(), 1);
  Serial.print("lbs");
  Serial.println();
  if(DHT11.humidity>50 || DHT11.temperature<0 || scale.get_units()>1){
    digitalWrite(7, HIGH);
  }else{
    digitalWrite(7, LOW);
  }
  delay(2000);
  
}
