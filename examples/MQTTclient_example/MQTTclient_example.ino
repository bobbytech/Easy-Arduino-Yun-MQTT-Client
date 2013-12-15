/*
*
*  MQTTclient, a MQTT (http://mqtt.com) client for Arduino Yun
*  Copyright 2013 (c) Martin Dal
*  Bobby Technologies I/S (http://bobbytechnologies.dk)
*
*  OpenWRT mosquitto client needed. Read the readme if in doubt! 
*  
*/

// include process library
#include <Process.h>
#include "MQTTclient.h"

#define MQTT_HOST "85.119.83.194" // test.mosquitto.org

void setup() {
    
  // start serial
  Serial.begin(9600);
  // remember the bridge!
  Bridge.begin();
  // begin the client library (initialize host)
  mqtt.begin(MQTT_HOST);
  
  // make some subscriptions
  mqtt.subscribe("test/mqttclient/topic1", someEvent);
  mqtt.subscribe("test/mqttclient/topic2", anotherEvent);
  mqtt.subscribe("test/mqttclient/topic3", loveMqtt);

}

void loop() {
  
  // check for incoming events
  mqtt.monitor();

}

// use callback function to work with your messages
void someEvent(const String& topic, const String& message) {
  
  // print the topic and message
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: "); 
  Serial.println(message); 
  
  int integer = 25;
  
  // publish an integer to a test topic
  mqtt.publish("test/mqttclient/publish1", integer);
  
}

void anotherEvent(const String& topic, const String& message) {
  
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: "); 
  Serial.println(message); 
  
  String someString = "hello myself";
  
  mqtt.publish("test/mqttclient/publish2", someString);
  
}

void loveMqtt(const String& topic, const String& message) {
  
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: "); 
  Serial.println(message); 
  
  float aFloat = 2.0f;
  
  mqtt.publish("test/mqttclient/publish2", aFloat);
  
}

