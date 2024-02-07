#include <dht.h>
#include "HX711.h"
dht DHT22;

#define dPIN 5
#define calibration_factor -7050.0
#define DOUT 3
#define CLK 2

HX711 scale(DOUT, CLK);

int relayPin=7;



void setup() {
 Serial.begin(9600);
 Serial.println("Humid(%), Temp(C), Weight(lbs), light");
 scale.set_scale(2500.f);
 scale.tare();
 pinMode(relayPin, OUTPUT);

}

void loop() {

  long val=analogRead(4);
  float temp=val*5.0/1024;
  int chk=DHT22.read11(dPIN);
  long lt=analogRead(A2);
  Serial.print(DHT22.humidity);
  Serial.print("%RH");
  Serial.print(",   ");
  Serial.print(temp);
  Serial.print("C");
  Serial.print(",   ");
  Serial.print(scale.get_units());
  Serial.print("lbs");
  Serial.print(",   ");
  Serial.print(lt);
  Serial.print(",   ");
  Serial.println();

  if( lt>450 && temp<0 && scale.get_units()>1 || scale.get_units()<-1 ){
    digitalWrite(7, HIGH);
  }else{
    digitalWrite(7, LOW);
  }
  if( lt>450 && DHT22.humidity>1 ){
    digitalWrite(7, HIGH);
  }else{
    digitalWrite(7, LOW);
  }
  delay(6000);
  
}
