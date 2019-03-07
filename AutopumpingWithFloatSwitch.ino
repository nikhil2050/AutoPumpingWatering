#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "nkjava2050"
#define DEVICE_ID "TestNMCU2"
#define DEVICE_CREDENTIAL "someSecretKey"

#define SSID "D-Link_DIR-81"
#define SSID_PASSWORD "Nikhil"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(D4, OUTPUT);                // Motor/LED
  pinMode(D5, OUTPUT);                // For MotorMode variable
  
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["motor"] << digitalPin(D4);
  thing["motorMode"] << digitalPin(D5);   // 0:Manual, 1:Automatic

  // resource output example (i.e. reading a sensor value)
  thing["footStorageBaseFloat"] >> outputValue(digitalRead(D0));
  // thing["headStorageBaseFloat"] >> outputValue(digitalRead(D1));
  thing["headStorageTopFloat"] >> outputValue(digitalRead(D2));
  
  // thing["millis"] >> outputValue(millis());
  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();

  if(digitalRead(D5)==HIGH) {   // If motorMode=Auto
    if(digitalRead(D0)==LOW){   // footStorage is not Empty
      if(digitalRead(D2)==HIGH){ // headStorage is not Full
        digitalWrite(D4, HIGH);   // Start motor
      } else {                  // headStorage is Full
        digitalWrite(D4, LOW);    // Stop motor
      }
    
    } else {                    // footStorage is Empty
      digitalWrite(D4, LOW);      // Stop motor
    }
  }
}
