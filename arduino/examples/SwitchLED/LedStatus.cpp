/*
 * This is the definition of the LedStatus class whose instance (object) will
 * receive and deserialize the incomming serial data.
 */

#include "LedStatus.h"

int LedStatus::getDataSize() {
  return SerializationTypes::SIZEOF_INTEGER;
}

void LedStatus::readData(SerializationInputStream& input) {
  status = input.readInteger();
}

void LedStatus::writeData(SerializationOutputStream& output) {
  output.writeInteger(status);
}
