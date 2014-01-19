Easy Arduino Yun MQTT Client
---

MQTTclient, a MQTT (http://mqtt.com) client for Arduino Yun, 
Copyright 2013 (c) Martin "Bobby" Dal, 
Bobby Technologies I/S (http://bobbytechnologies.dk)

---

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. 

---

Introduction 
---

This MQTT library for Arduino Yun use Lininio processes to facilitate MQTT communication. Different from already existing PubSubClient (https://github.com/mcollina/mqtt_on_the_yun), publishing floats and integers have been made easier without previous conversion to char*. Also topics will have their own callback function, with topic and message string provided as parameters, to make parsing messages easier and hopefully let you create IoT things faster! 

! Remember to rename library folder, as arduino IDE doesn't support hyphens !


Dependencies 
---

A mosquitto client on the lininio side(openWRT) is needed, and can be installed using the package manager (http://arduino.cc/en/Tutorial/YunPackageManager). Just run these two commands on your root@yun.local to install:

```c
opkg update
opkg install mosquitto mosquitto-client libmosquitto
```

Documentation
---

To initialize the MQTTclient, call this function and pass your selected server and port as arguments:
```c
mqtt.begin("test.mosquitto.org", 1883);
```

---

To subscribe to a topic, call this function and put topic as the first argument, and define a name of the callback function:
```c
mqtt.subscribe("test/topic", someCallback);
```

---

Subscription to all sub topics is also possible, just place the #:
```c
mqtt.subscribe("test/topic/#", someCallback);
```

---

To publish a message to a topic, call this function and put topic as the first argument, and a string, float or integer as the second:
```c
mqtt.publish("test/topic", "message");
```

---

Remember to check for messages in the loop():
```c
mqtt.monitor();
```

---

Define a function for your incoming messages using this syntax (subtopic will contain only the rest of the topicstring in '#' subscriptions):
```c
void someCallback(const String& topic, const String& subtopic, const String& message) { /* go nutz */ }
```

Disclaimer
---

This is the very first version. Amongst other things both QoS and secure client connection is not provided yet! Feel free to contribute!
<<<<<<< HEAD

=======
>>>>>>> 96174d55de1c0fa8257d10575360844c358e62d0


