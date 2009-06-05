/*
 * This is the definition of the Message class whose instance (object) is going
 * to be serialized and sent via the serial connection.
 */

#include "Message.h"

int Message::getDataSize() {
  return SerializationTypes::SIZEOF_INTEGER + strlen(message);
}

void Message::readData(SerializationInputStream& input) {
  input.readString(message);
}

void Message::writeData(SerializationOutputStream& output) {
  output.writeString(message);
}

