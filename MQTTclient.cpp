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

#include "MQTTclient.h"

MQTTclient::MQTTclient() { }

void MQTTclient::begin(const String& host, const unsigned short& port) {
	_host = host;
	_port = String(port);
}

void MQTTclient::monitor() {

	for(int i = 0; i < MAX_TOPICS; i++) {
		if (_cbs[i].assigned) {
			if (_cbs[i].input.available() > 0 && !_cbs[i].reading) {
				read(_cbs[i].input, _cbs[i].listenTopic, _cbs[i].callback, _cbs[i].reading);
			}
		}
	}

}

bool MQTTclient::publish(const String& topic, const int& msg) {
	return publish(topic, String(msg));
}

bool MQTTclient::publish(const String& topic, const float& msg) {
	return publish(topic, String(msg));
}

bool MQTTclient::publish(const String& topic, const String& msg) {

	_output.begin(MQTT_PUB);
    _output.addParameter(MQTT_PARAM_HOST);
    _output.addParameter(_host);
    _output.addParameter(MQTT_PARAM_PORT);
    _output.addParameter(_port);
    _output.addParameter(MQTT_PARAM_TOPIC);
    _output.addParameter(topic);
    _output.addParameter(MQTT_PARAM_MSG);
    _output.addParameter(msg);
    _output.run();

    if(_output.exitValue() == 0) {
    	return true;
    }
    else {
    	return false;
    }

}

void MQTTclient::subscribe(const String& listenTopic, callbackFunction callback) {

	bool assigned = false;
	char i = 0;

	while (!assigned) {
        if(!_cbs[i].assigned) {
            _cbs[i].listenTopic = listenTopic;
            _cbs[i].callback = callback;
            _cbs[i].assigned = true;
            _cbs[i].reading = false;

            _cbs[i].input.begin(MQTT_SUB);	
    		_cbs[i].input.addParameter(MQTT_PARAM_HOST);
    		_cbs[i].input.addParameter(_host);
    		_cbs[i].input.addParameter(MQTT_PARAM_PORT);
    		_cbs[i].input.addParameter(_port);
    		_cbs[i].input.addParameter(MQTT_PARAM_TOPIC);
    		_cbs[i].input.addParameter(listenTopic);
    		_cbs[i].input.addParameter(MQTT_PARAM_VERBOSE); 
    		_cbs[i].input.runAsynchronously();	

            assigned = true;

        }
        i++;
    }

}

void MQTTclient::unsubscribe(const String& topic) {

	for(int i = 0; i < MAX_TOPICS; i++) {
		if (_cbs[i].assigned) {
			if (_cbs[i].listenTopic == topic) {
				_cbs[i].input.close();
				_cbs[i].assigned = false;
				_cbs[i].listenTopic = "";
			}
		}
	}

}

void MQTTclient::read(Process& input, const String& listenTopic, callbackFunction callback, bool& reading) {

	String inc;
	String topic;
	String msg;
	char inchar;
	bool tread = false;
	bool done = false;



	while(input.available() > 0 && (inchar = input.read()) != '\n') {

		if (inchar != '\r' && inchar != -1) {
		    if(inchar == ' ' && !tread) {
		       	topic = inc;
		       	inc = "";
		       	tread = true;
		    }
		    else {
		      	if(tread) {
		          	msg += inchar; 
		          	inc = "";
		          	done = true;
		      	}
		      	else {
		          	inc += inchar; 
		      	}
		    }    
		}        
	}

	if(done) {

		String subtopic = topic.substring(listenTopic.length()-1);
		topic = listenTopic.substring(0, listenTopic.length()-2);

        callback(topic, subtopic ,msg);
        reading = false;
    	
	  	input.flush(); 

	}

}

MQTTclient mqtt;

