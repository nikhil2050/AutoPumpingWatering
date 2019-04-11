#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "nkjava2050"
#define DEVICE_ID "TestNMCU2"
#define DEVICE_CREDENTIAL "someSecretKey2"

#define SSID "D-Link_DIR-81"
#define SSID_PASSWORD "Nikhil"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(9600); 
  pinMode(D0, OUTPUT);                // Motor/LED
  pinMode(D5, OUTPUT);                // HIGH:Auto, LOW:Manual
  digitalWrite(D5, HIGH);
  
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  // OUTPUT
  thing["motor"] << digitalPin(D0);
  thing["motorMode"] << digitalPin(D5);

  // resource output example (i.e. reading a sensor value)
  // INPUT
  thing["headStorageBaseFloat"] >> outputValue(digitalRead(D1));
  thing["headStorageTopFloat"] >> outputValue(digitalRead(D2));
  thing["footStorageBaseFloat"] >> outputValue(digitalRead(D7));
  thing["motorManualBtn"] >> outputValue(digitalRead(D6));
  
  // thing["millis"] >> outputValue(millis());
  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
  Serial.print("motorMode");   Serial.println(digitalRead(D5));
  if(digitalRead(D5)==HIGH) {   // If motorMode=Auto
    if(digitalRead(D7)==LOW){   // footStorage is not Empty
      
      Serial.print("footStorage Base D7(footStorage Filled)::");  Serial.println(digitalRead(D7));
      Serial.print("headStorage Base D1::");Serial.println(digitalRead(D1));
      Serial.print("headStorage Top D2::"); Serial.println(digitalRead(D2));
      
      if(digitalRead(D1)==LOW && digitalRead(D2)==LOW){         // headStorage is Full
        digitalWrite(D0, LOW);              // Stop motor
      } else if(digitalRead(D1)==HIGH && digitalRead(D2)==HIGH){ // headStorage is not Full
        digitalWrite(D0, HIGH);             // Start motor
      }
      Serial.print("motor D0 (New)::");           Serial.println(digitalRead(D0));
    
    } else {                            // footStorage is Empty
      digitalWrite(D0, LOW);                // Stop motor
      Serial.print("motor D0 (footStorage Empty)::");           Serial.println(digitalRead(D0));
    }
  
  } else {                      // If motorMode=Manual
    digitalWrite(D0, digitalRead(D6));      // Motor works on D6 btn
  }
  Serial.println("--");
  delay(1000);
}

