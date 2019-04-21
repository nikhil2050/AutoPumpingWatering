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
  pinMode(D6, OUTPUT);                // 0:OFF, 1:ON
  digitalWrite(D6, LOW);
  
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  // OUTPUT
  thing["motor"] << digitalPin(D0);
  thing["motorMode"] << digitalPin(D5);
  thing["motorManualBtn"] << digitalPin(D6);

  // resource output example (i.e. reading a sensor value)
  // INPUT
  thing["workerStorageBottomFloat"] >> outputValue(digitalRead(D1));
  thing["workerStorageTopFloat"] >> outputValue(digitalRead(D2));   
  thing["masterStorageBottomFloat"] >> outputValue(digitalRead(D7));
  
  // thing["millis"] >> outputValue(millis());
  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
  Serial.print("motorMode");   Serial.println(digitalRead(D5));
  if(digitalRead(D5)==HIGH) {   // If motorMode=Auto
    if(digitalRead(D7)==LOW){   // masterStorage is not Empty
      
      Serial.print("masterStorage Bottom D7(masterStorage Filled)::");  Serial.println(digitalRead(D7));
      Serial.print("workerStorage Bottom D1::");Serial.println(digitalRead(D1));
      Serial.print("workerStorage Top D2::"); Serial.println(digitalRead(D2));
      
      if(digitalRead(D1)==LOW && digitalRead(D2)==LOW){         // workerStorage is Full
        digitalWrite(D0, LOW);              // Stop motor
      } else if(digitalRead(D1)==HIGH && digitalRead(D2)==HIGH){ // workerStorage is not Full
        digitalWrite(D0, HIGH);             // Start motor
      }
      Serial.print("motor D0 (New)::");           Serial.println(digitalRead(D0));
    
    } else {                            // masterStorage is Empty
      digitalWrite(D0, LOW);                // Stop motor
      Serial.print("motor D0 (masterStorage Empty)::");           Serial.println(digitalRead(D0));
    }
  
  } else {                      // If motorMode=Manual
    digitalWrite(D0, digitalRead(D6));      // Motor works on D6 btn
  }
  delay(1000);
  Serial.println("--");
}
