/*
 * The SimpleSerialization library allows you to send and receive simple objects
 * via a serial connection. Those objects can contain integer and floating point
 * values and strings.
 *  
 * File:   Serialization.h
 * Version: 1.0
 * Author: jarontec gmail com
 */

#ifndef _SIMPLESERIALIZATION_H
#define	_SIMPLESERIALIZATION_H

#include "HardwareSerial.h"
#include "WProgram.h"

class SerializationData;

/*
 * SerializationTypes
 */
class SerializationTypes {
  public:
    static const int SIZEOF_INTEGER = 4;
    static const int SIZEOF_FLOAT = 4;
    static const int SIZEOF_STRING = 4;
    static long bytesToInteger(byte b[SIZEOF_INTEGER]);
    static void integerToBytes(long val, byte b[SIZEOF_INTEGER]);
    static long floatToIntBits(float val);
    static float intBitsToFloat(long bits);
};
// the float to integer conversion union
union u { long l; float d; };

/*
 * SerializationInputStream
 */
class SerializationInputStream {
  public:
    SerializationInputStream(byte* buffer, short bufferSize);
    ~SerializationInputStream();
    long readInteger();
    float readFloat();
    void readString(char* str);
  private:
    byte* buffer;
    int pos;
    int size;
    int read();
};

/*
 * SerializationOutputStream
 */
class SerializationOutputStream {
  public:
    static const short DEFAULT_BUFFER_SIZE = 512;
    SerializationOutputStream();
    SerializationOutputStream(short bufferSize);
    ~SerializationOutputStream();
    void writeInteger(long val);
    void writeFloat(float val);
    void writeString(char* str);
    byte* getBuffer();
    int getPos() { return(pos); };
  private:
    byte* buffer;
    int pos;
    int size;
    void initialize(short bufferSize);
    void write(int b);
    void write(byte b[], int length);
};

/*
 * SerializationSerialReader
 */
class SerializationSerialReader {
  public:
    SerializationSerialReader(SerializationData* data);
    SerializationSerialReader(SerializationData* data, short bufferSize);
    ~SerializationSerialReader();
    void processData(byte b);
  private:
    static const short DEFAULT_BUFFER_SIZE = 512;
    SerializationData* data;
    byte* buffer;
    short bufferCounter;
    short bufferSize;
    short preambleCounter;
    short postambleCounter;
    boolean doCollectData;
    byte preamble[SerializationTypes::SIZEOF_INTEGER];
    byte postamble[SerializationTypes::SIZEOF_INTEGER];
    void initialize(SerializationData* data, short bufferSize);
    void collectData(byte b);
};

/*
 * SerializationData
 */
class SerializationData {
  public:
    SerializationData();
    virtual ~SerializationData();
    long getPreamble();
    void setPreamble(long preamble);
    long getChecksum();
    void setChecksum(long checksum);
    long getPostamble();
    void setPostamble(long postamble);
    int getSize();
    void read(SerializationInputStream& input);
    void write(SerializationOutputStream& output);
    void (*updateCallback)(SerializationData* data);
    void setUpdateCallback(void (*ptr)(SerializationData*));
    virtual void readData(SerializationInputStream& input) { };
    virtual void writeData(SerializationOutputStream& output) { };
    virtual int getDataSize() { return 0; };
  private:
    long preamble;
    long checksum;
    long postamble;
};

/*
 * SerializationSerialConnection
 */
class SerializationSerialConnection {
  public:
    SerializationSerialConnection();
    void addDeserializableData(SerializationData* data);
    void begin();
    void begin(long speed);
    void begin(HardwareSerial* port, long speed);
    void processInput();
    void write(SerializationData* data);
  private:
    static const long DEFAULT_SPEED = 115200;
    static const short MAXIMUM_READERS = 8;
    HardwareSerial* port;
    SerializationSerialReader* readers[MAXIMUM_READERS];
    int readerCounter;
    void process(byte b);
};

extern SerializationSerialConnection SimpleSerialization;

#endif	/* _SIMPLESERIALIZATION_H */

