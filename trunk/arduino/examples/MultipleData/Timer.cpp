/*
 * This is the definition of the Timer class whose instance (object) is going
 * to be serialized and sent via the serial connection.
 * In its constructor method this class defines new values for the preamble and
 * the postamble. That makes the instances of this class distinguishable from
 * any other objects that are serialized.
 */

#include "Timer.h"

Timer::Timer() {
  setPreamble(11223344);  // just random values to
  setPostamble(44332211); // identify the object
}

int Timer::getDataSize() {
  int dataSize = SerializationTypes::SIZEOF_INTEGER; // hours
  dataSize += SerializationTypes::SIZEOF_INTEGER;    // minutes
  dataSize += SerializationTypes::SIZEOF_INTEGER;    // seconds
  return (dataSize);
}

void Timer::readData(SerializationInputStream& input) {
  hours = input.readInteger();
  minutes = input.readInteger();
  seconds = input.readInteger();
}

void Timer::writeData(SerializationOutputStream& output) {
  output.writeInteger(hours);
  output.writeInteger(minutes);
  output.writeInteger(seconds);
}

