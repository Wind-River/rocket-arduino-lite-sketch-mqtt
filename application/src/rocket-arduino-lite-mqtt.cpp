/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. 
 * You may obtain a copy of the License at 
 * 
 * http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES 
 * OR CONDITIONS OF ANY KIND, either express or implied. See the License for
 * the specific language governing permissions and limitations under the License. 
 */

#include "Serial.h"
#include "Ethernet.h" 
#include "MqttClient.h"

const int pubWaitCount = 20;
int pubCount = 0;
uint8_t qos = 1;

void MQTTMessageReceived(char* topic, byte* payload, unsigned int length) {
    Serial.print("Rocket received message  [");
    Serial.print(topic);
    Serial.print("] ");
  
    for (int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();  
}

void setup() {
    Serial.println("Bringing up Ethernet interface with DHCP address");
   
   // Bring up the inteface with a DHCPed address (MACC address param ignored; will use real MAC address)
    Ethernet.begin(); // Bring up interface with H/W MAC address and DHCP Ethernet Address
  
    MQTT_Client.setCallback(MQTTMessageReceived);
    MQTT_Client.setServer("iot.eclipse.org", 1883);
}

void loop() {    
    if (!MQTT_Client.connected()) {    
        byte mac[] = { 1, 2, 3, 4, 5, 6 };
        char id[] = "AABBCCDDEEFF"; // will be replaced by MAC address
         Ethernet.getMacAddress(mac) ;   
        sprintf(id,"%X%X%X%X%X%X%X%X%X%X%X%X", (mac[0] >> 4), (mac[0] & 0xf), (mac[1] >> 4), (mac[1] & 0xf), (mac[2] >> 4), (mac[2] & 0xf), (mac[3] >> 4), (mac[3] & 0xf), (mac[4] >> 4), (mac[4] & 0xf), (mac[5] >> 4), (mac[5] & 0xf));

      if (MQTT_Client.connect(id)) {
          if (!MQTT_Client.subscribe("rocket/greeting", qos)) {
             Serial.println("Subscribing failed");
          }
      } else {
        Serial.println("Connection failed");
      }
  } else {   
        if (pubCount < pubWaitCount) {
            pubCount++;
        } else {
            pubCount = 0;
            if (!MQTT_Client.publish("rocket/greeting", "hello from rocket", qos)){
                Serial.println("Publishing Failed");
            }      
        }
        MQTT_Client.loop();
  }
  delay(100);
}

