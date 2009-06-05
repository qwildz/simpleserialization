/*
 * A very simple example that sends a string from the Arduino containing the
 * message "Hello Arduino!". Have a look the according Processing (PDE) example to
 * see how the message is received.
 *
 * The SimpleSerialization library allows you to send and receive simple objects
 * via a serial connection. Those objects can contain integer and floating point
 * values and strings.
 * The first step on using the SimpleSerialization library is to create a class
 * that will contain the data (integers, floats, strings) and the methods
 * (getDataSize, readData, writeData) that allow the object to be serialized and
 * deserialized.
 * The next steps are the initialization of the serial connection in the Arduino
 * setup function and in this case the periodically sending of the data in the 
 * loop function.
 */

#include <SimpleSerialization.h>

#include "Message.h"

long connectionSpeed = 115200;

void setup() {
  SimpleSerialization.begin(connectionSpeed);
}

void loop() {
  Message myMessage;
  myMessage.setMessage("Hello Arduino!");
  SimpleSerialization.write(&myMessage);
  delay(1000);
}
