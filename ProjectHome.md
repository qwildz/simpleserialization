The SimpleSerialization library provides the functionality to serialize and deserialize objects to streams that then can be sent via a serial connection.
Currently there is an implementation of the library for the Arduino microcontroller so that a Java application and an Arduino can communicate via the serial interface.

The SimpleSerilaization library could be used to debug and remote control an Arduino or to do a hardware-in-the-loop simulation.
An example SimpleSerialization application could be to feed an Arduino with GPS data at 5Hz and attitude data at 30Hz. In return the Arduino would send the calculated actuator commands back at a rate of 10Hz. All this data would be exchanged via a single serial connection.

The SimpleSerialization library is a part of my <a href='http://code.google.com/p/uavplayground/'>UAV Playground</a> project where I explore various aspects of UAVs like microcontrollers, simulators and remote controlled model airplanes.
Follow me on [Twitter](http://twitter.com/jarontec) if you want to know on what part I'm currently working on.


A screenshot of a basic SimpleSerialization application in the Arduino IDE

![http://simpleserialization.googlecode.com/files/SimpleSerialization-1.0-Arduino-Screenshot.jpg](http://simpleserialization.googlecode.com/files/SimpleSerialization-1.0-Arduino-Screenshot.jpg)

A screenshot of a basic SimpleSerialization application in the Processing IDE

![http://simpleserialization.googlecode.com/files/SimpleSerialization-1.0-Processing-Screenshot.jpg](http://simpleserialization.googlecode.com/files/SimpleSerialization-1.0-Processing-Screenshot.jpg)