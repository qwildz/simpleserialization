/*
 * This is the declaration of the Message class whose instance (object) is going
 * to be serialized and sent via the serial connection.
 * 
 */

#ifndef _MESSAGE_H
#define	_MESSAGE_H

#include "SimpleSerialization.h"

class Message : public SerializationData {
public:
    int getDataSize();
    void readData(SerializationInputStream& input);
    void writeData(SerializationOutputStream& output);
    char* getMessage() { return message; };
    void setMessage(char *message) { strcpy(this->message, message); };
    float getPI() { return pi; }
    void setPI(float pi) { this->pi = pi; }
private:
    char message[32];
    float pi;
};

#endif	/* _MESSAGE_H */
