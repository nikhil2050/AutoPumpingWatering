#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "nkjava2050"
#define DEVICE_ID "TestNMCU2"
#define DEVICE_CREDENTIAL "someSecretKey2"

#define SSID "D-Link_DIR-81"
#define SSID_PASSWORD "Nikhil"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(D4, OUTPUT);                // Motor/LED
  
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  // OUTPUT
  thing["motor"] << digitalPin(D4);

  // resource output example (i.e. reading a sensor value)
  // INPUT
  thing["footStorageBaseFloat"] >> outputValue(digitalRead(D0));
  thing["headStorageBaseFloat"] >> outputValue(digitalRead(D1));
  thing["headStorageTopFloat"] >> outputValue(digitalRead(D2));
  thing["motorModeBtn"] >> outputValue(digitalRead(D5));  // 0:Manual, 1:Automatic
  thing["motorBtn"] >> outputValue(digitalRead(D6));
  
  // thing["millis"] >> outputValue(millis());
  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();

  if(digitalRead(D5)==HIGH) {   // If motorMode=Auto
    if(digitalRead(D0)==LOW){   // footStorage is not Empty
      
      if(digitalRead(D2)==LOW){         // headStorage is Full
        digitalWrite(D4, LOW);              // Stop motor
      } else if(digitalRead(D1)==HIGH){ // headStorage is not Full
        digitalWrite(D4, HIGH);             // Start motor
      }
    
    } else {                            // footStorage is Empty
      digitalWrite(D4, LOW);                // Stop motor
    }
  
  } else {                      // If motorMode=Manual
    if(digitalRead(D6) == HIGH){
      digitalWrite(D4, HIGH); 
    } else {
      digitalWrite(D4, LOW);       
    }
  }
}
