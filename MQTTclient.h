/*
*
*	 MQTTclient, a MQTT (http://mqtt.com) client for Arduino Yun
*	 Copyright 2013 (c) Martin "Bobby" Dal
*	 Bobby Technologies I/S (http://bobbytechnologies.dk)
*
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*    THE SOFTWARE. 
*
*/

#ifndef MQTTclient_h
#define MQTTclient_h

#include <Arduino.h>  
#include <Process.h>

#define MQTT_PUB "mosquitto_pub"
#define MQTT_SUB "mosquitto_sub"

#define MQTT_PARAM_HOST "-h"
#define MQTT_PARAM_TOPIC "-t"
#define MQTT_PARAM_MSG "-m"
#define MQTT_PARAM_VERBOSE "-v"
#define MQTT_PARAM_PORT "-p"

#define MAX_TOPICS 5

typedef void (*callbackFunction)(const String& topic, const String& subtopic, const String& message);

struct Callbacks {
    
    String listenTopic;
    callbackFunction callback;
    bool assigned;
    Process input;
    bool reading;
    
};

class MQTTclient {

	public:

		MQTTclient();

		void begin(const String& host, const unsigned short& port);
		void monitor();

		bool publish(const String& topic, const String& msg);
		bool publish(const String& topic, const int& msg);
		bool publish(const String& topic, const float& msg);

		void subscribe(const String& topic, callbackFunction callback);
		void unsubscribe(const String& topic);

	private:

		void read(Process& input, const String& listenTopic, callbackFunction callback, bool& reading);

		Callbacks _cbs[MAX_TOPICS];

		Process _output;
		String _host;
		String _port;

};

extern MQTTclient mqtt;

#endif