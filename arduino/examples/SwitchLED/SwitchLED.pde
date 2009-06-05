/*
 * A very simple example that receives an integer value and turns an LED on 
 * pin 13 on or off according to the value. Have a look at the SwitchLED
 * Processing (PDE) example to see how the value is sent.
 * 
 * The SimpleSerialization library allows you to send and receive simple objects
 * via a serial connection. Those objects can contain integer and floating point
 * values and strings.
 * The first step on using the SimpleSerialization library is to create a class
 * that will contain the data (integers, floats, strings) and the methods
 * (getDataSize, readData, writeData) that allow the object to be serialized and
 * deserialized.
 * The next step is to provide a callback function that will be called as soon
 * as data is received via the serial connection.
 * The last steps are the initialization of the serial connection in the Arduino
 * setup function and in this case the periodically poll for incoming data in
 * the loop function.
 */

#include <SimpleSerialization.h>

#include "LedStatus.h"

int ledPin = 13;
long connectionSpeed = 115200;
LedStatus ledStatus;

/*
 * This is the callback function that is called whenever the data is updated.
 */
void dataUpdate(SerializationData *data) {
  if (((LedStatus *)data)->getStatus() == 1)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  ledStatus.setUpdateCallback(&dataUpdate);
  SimpleSerialization.begin(connectionSpeed);
  SimpleSerialization.addDeserializableData(&ledStatus);
}

void loop() {
  SimpleSerialization.processInput();
}
