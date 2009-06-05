/*
 * This example demonstrates how different data structures can be sent via a
 * serial connection at different frequencies. Have a look the according
 * Processing (PDE) example to see how the data is received.
 *
 * The SimpleSerialization library allows you to send and receive simple objects
 * via a serial connection. Those objects can contain integer and floating point
 * values and strings.
 * The first step on using the SimpleSerialization library is to create the
 * classes that will contain the data (integers, floats, strings) and the methods
 * (getDataSize, readData, writeData) that allow the object to be serialized and
 * deserialized.
 * The next steps are the initialization of the serial connection in the Arduino
 * setup function and in this case the periodically sending of the data in the 
 * loop function.
 */

#include <stdlib.h>

#include <SimpleSerialization.h>

#include "Message.h"
#include "Timer.h"

long connectionSpeed = 115200;

void setup() {
  SimpleSerialization.begin(connectionSpeed);
}

void loop() {
  // Get the current timer values
  long m = millis();
  long seconds = m / 1000;
  m = m % 1000;
  long minutes = seconds / 60;
  seconds = seconds % 60;
  long hours = minutes / 60;
  minutes = minutes % 60;
  hours = hours % 24;

  // Send the timer values every second
  Timer myTimer;
  myTimer.setHours(hours);
  myTimer.setMinutes(minutes);
  myTimer.setSeconds(seconds);
  SimpleSerialization.write(&myTimer);
  
  // Send a message every third second
  if (seconds % 3 == 0) {
    Message myMessage;
    myMessage.setMessage("Arduino's PI");
    myMessage.setPI(3.14159);
    SimpleSerialization.write(&myMessage);
  }

  delay(1000);
}
