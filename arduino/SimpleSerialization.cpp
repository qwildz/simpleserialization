/*
 * The SimpleSerialization library allows you to send and receive simple objects
 * via a serial connection. Those objects can contain integer and floating point
 * values and strings.
 *  
 * File:   Serialization.cpp
 * Version: 1.0
 * Author: jarontec gmail com
 */

#include "SimpleSerialization.h"

void* operator new(size_t size) { return malloc(size); }
void operator delete(void* ptr) { free(ptr); } 

/*
 * SerializationTypes
 */
long SerializationTypes::bytesToInteger(byte b[SerializationTypes::SIZEOF_INTEGER]) {
  long val = 0;
  val = ((long)b[0]) << 24;
  val |= ((long)b[1]) << 16;
  val |= ((long)b[2]) << 8;
  val |= b[3];
  return val;
}

void SerializationTypes::integerToBytes(long val, byte b[SerializationTypes::SIZEOF_INTEGER]) {
  b[0] = (val >> 24) & 0xff;
  b[1] = (val >> 16) & 0xff;
  b[2] = (val >> 8) & 0xff;
  b[3] = val & 0xff;
}

long SerializationTypes::floatToIntBits(float val) {
  union u u;
  u.d = val;
  long e = u.l & 0x7f800000;
  long f = u.l & 0x007fffff;

  if (e == 0x7f800000 && f != 0) {
    u.l = 0x7fc00000;
  }

  return u.l;
}

float SerializationTypes::intBitsToFloat(long bits) {
  union u u;
  u.l = bits;
  return u.d;
}

/*
 * SerializationInputStream
 */
SerializationInputStream::SerializationInputStream(byte* buffer, short bufferSize) {
  this->buffer = buffer;
  pos = 0;
  size = bufferSize;
}

SerializationInputStream::~SerializationInputStream() {
}

long SerializationInputStream::readInteger() {
  byte b[SerializationTypes::SIZEOF_INTEGER];
  for (int i = 0; i < SerializationTypes::SIZEOF_INTEGER; ++i) {
      b[i] = (byte)read();
  }
  return SerializationTypes::bytesToInteger(b);
}

float SerializationInputStream::readFloat() {
  return SerializationTypes::intBitsToFloat(readInteger());
}

void SerializationInputStream::readString(char* str) {
  int length = (int)readInteger();

  for (int i = 0; i < length; ++i) {
    str[i] = (char)read();
  }
  str[length] = '\0';
}

int SerializationInputStream::read() {
  if (pos < size) {
    return buffer[pos++] & 0xff;
  }
  else {
    return -1;
  }
}

/*
 * SerializationOutputStream
 */
SerializationOutputStream::SerializationOutputStream() {
  initialize(DEFAULT_BUFFER_SIZE);
}

SerializationOutputStream::SerializationOutputStream(short bufferSize) {
  initialize(bufferSize);
}

SerializationOutputStream::~SerializationOutputStream() {
  free(buffer);
}

void SerializationOutputStream::initialize(short bufferSize) {
  buffer = (byte*)malloc(bufferSize* sizeof(byte));
  pos = 0;
  size = bufferSize;
}

void SerializationOutputStream::writeInteger(long val) {
  byte b[SerializationTypes::SIZEOF_INTEGER];
  SerializationTypes::integerToBytes(val, b);
  write(b, SerializationTypes::SIZEOF_INTEGER);
}

void SerializationOutputStream::writeFloat(float val) {
  long d = SerializationTypes::floatToIntBits(val);
  writeInteger(d);
}

void SerializationOutputStream::writeString(char* str) {
  int length = strlen(str);

  // write the length of the string first
  writeInteger(length);

  // write the characters
  for (int i = 0; i < length; ++i) {
    write((int)str[i]);
  }
}

byte* SerializationOutputStream::getBuffer() {
    return buffer;
}

void SerializationOutputStream::write(int b) {
  if (pos < size) {
    buffer[pos++] = (byte)b;
  }
}

void SerializationOutputStream::write(byte b[], int length) {
  for (int i = 0; (i < length) & (i < size); ++i) {
    buffer[pos++] = b[i];
  }
}

/*
 * SerializationSerialReader
 */
SerializationSerialReader::SerializationSerialReader(SerializationData* data) {
  initialize(data, DEFAULT_BUFFER_SIZE);
}

SerializationSerialReader::SerializationSerialReader(SerializationData* data, short bufferSize) {
  initialize(data, bufferSize);
}

SerializationSerialReader::~SerializationSerialReader() {
  free(buffer);
}

void SerializationSerialReader::initialize(SerializationData* data, short bufferSize) {
  this->data = data;
  this->bufferSize = bufferSize;

  buffer = (byte*)malloc(bufferSize* sizeof(byte));
  bufferCounter = 0;

  preambleCounter = 0;
  postambleCounter = 0;
  doCollectData = false;

  SerializationTypes::integerToBytes(data->getPreamble(), preamble);
  SerializationTypes::integerToBytes(data->getPostamble(), postamble);
}

void SerializationSerialReader::processData(byte b) {
  if (doCollectData) {
    // if the collect data flag is set (after receiving the preamble) then collect the serial data
    collectData(b);
  }
  else {
    if (b == preamble[preambleCounter]) {
      // if the data byte is a preamble sequence byte then collect the preamble
      buffer[preambleCounter] = b;
      ++preambleCounter;
    }
    else {
      // if the data byte is not a preamble sequence byte then reset the preamble counter
      preambleCounter = 0;
    }
    // if the whole preamble sequence is received...
    if (preambleCounter == SerializationTypes::SIZEOF_INTEGER) {
      // reset the preamble counter to be ready to count the next preamble seuquence byte
      preambleCounter = 0;
      // start collecting the data
      bufferCounter = SerializationTypes::SIZEOF_INTEGER - 1; // the preamble is already stored in the buffer
      doCollectData = true;
    }
  }
}

void SerializationSerialReader::collectData(byte b) {
  // increase the buffer counter but prevent a buffer overflow
  if (bufferCounter < bufferSize) {
    ++bufferCounter;
  }

  // fill the buffer
  buffer[bufferCounter] = b;

  // check for a postamble sequence byte
  if (b != postamble[postambleCounter]) {
    postambleCounter = 0;
  }
  else {
    ++postambleCounter;
  }

  // if the whole postamble sequence is received...
  if (postambleCounter == SerializationTypes::SIZEOF_INTEGER) {
    // do a checksum test before deserializing the data
    byte checksumBytes[SerializationTypes::SIZEOF_INTEGER];
    for (int i = 0; i < SerializationTypes::SIZEOF_INTEGER; ++i) {
      checksumBytes[i] = buffer[i+SerializationTypes::SIZEOF_INTEGER];
    }
    // deserialize the data and fire an update event (callback routine)
    if (SerializationTypes::bytesToInteger(checksumBytes) == bufferCounter + 1) {
      SerializationInputStream input(buffer, bufferCounter);
      data->read(input);
      if (data->updateCallback != NULL) {
        (*(data->updateCallback))(data);
      }
    }
    else {
      // Exception handling
    }
    // reset the postamble counter to be ready to count the next postamble seuquence byte
    postambleCounter = 0;
    // stop collecting the data (start waiting for the preamble sequence)
    doCollectData = false;
  }
}

/*
 * SerializationData
 */
SerializationData::SerializationData() {
  preamble = 123456789;   // default preamble
  postamble = 987654321;  // default postamble
  updateCallback = NULL;
}

SerializationData::~SerializationData() {

}

long SerializationData::getPreamble() {
  return preamble;
}

void SerializationData::setPreamble(long preamble) {
  this->preamble = preamble;
}

// the checksum is calculated at runtime
long SerializationData::getChecksum() {
  return checksum;
}

void SerializationData::setChecksum(long checksum) {
  this->checksum = checksum;
}

long SerializationData::getPostamble() {
  return postamble;
}

void SerializationData::setPostamble(long postamble) {
  this->postamble = postamble;
}

void SerializationData::read(SerializationInputStream& input) {
  setPreamble(input.readInteger());
  setChecksum(input.readInteger());

  readData(input); // let the subclass read its data

  setPostamble(input.readInteger());
}

void SerializationData::write(SerializationOutputStream& output) {
    output.writeInteger(getPreamble());
    output.writeInteger(getSize());

    writeData(output); // let the subclass write its data

    output.writeInteger(getPostamble());
}

int SerializationData::getSize() {
  int size = SerializationTypes::SIZEOF_INTEGER; // preamble
  size += SerializationTypes::SIZEOF_INTEGER;    // checksum
  size += getDataSize();                         // subclass' data size
  size += SerializationTypes::SIZEOF_INTEGER;    // postamble

  return size;
}

void SerializationData::setUpdateCallback(void (*ptr)(SerializationData*)) {
  updateCallback = ptr;
}

/*
 * SerializationSerialConnection
 */
SerializationSerialConnection::SerializationSerialConnection() {
  readerCounter = 0;
}

void SerializationSerialConnection::begin() {
  Serial.begin(DEFAULT_SPEED);
  this->port = &Serial;
}

void SerializationSerialConnection::begin(long speed) {
  Serial.begin(speed);
  this->port = &Serial;
}

void SerializationSerialConnection::begin(Stream * port) {
  this->port = port;
}

void SerializationSerialConnection::addDeserializableData(SerializationData* data) {
  readers[readerCounter] = new SerializationSerialReader(data);
  ++readerCounter;
}

void SerializationSerialConnection::processInput() {
  if (port->available() > 0) {
    byte b = port->read();
    process(b);
  }
}

void SerializationSerialConnection::write(SerializationData* data) {
  SerializationOutputStream out;
  data->write(out);
  byte* buffer = out.getBuffer();
  for (int i = 0; i < out.getPos(); ++i) {
    port->print(buffer[i]);
  }
}

void SerializationSerialConnection::process(byte b) {
  for (int i = 0; i < readerCounter; i++) {
    readers[i]->processData(b);
  }
}

// make an instance for simplified usage
SerializationSerialConnection SimpleSerialization;
