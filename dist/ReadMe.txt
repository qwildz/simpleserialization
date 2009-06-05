SimpleSerialization
-------------------

The SimpleSerialization library provides the functionality to serialize and
deserialize objects to streams that then can be sent via a serial connection.
Currently there is an implementation of the library for Java and the Arduino
microcontroller so that a Java application and an Arduino can communicate via
the serial interface.

The SimpleSerilaization library could be used to debug and remote control an
Arduino or to do a hardware-in-the-loop simulation.
An example SimpleSerialization application could be to feed an Arduino with GPS
data at 5Hz and attitude data at 30Hz. In return the Arduino would send the
calculated actuator commands back at a rate of 10Hz. All this data would be
exchanged via a single serial connection.

Project information and the source code can be found at:
http://code.google.com/p/simpleserialization/

The SimpleSerialization library is a part of my project UAV Playground where I
explore various aspects of UAVs like microcontrollers, simulators and remote
controlled model airplanes:
http://code.google.com/p/uavplayground/

The SimpleSerialization library is released under GNU Lesser General Public
License (LGPL).

Copyright 2009 jarontec gmail com