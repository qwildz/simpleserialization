/*
 * This is the declaration of the LedStatus class whose instance (object) will
 * receive and deserialize the incomming serial data.
 */

#ifndef _LEDSTATUS_H
#define	_LEDSTATUS_H

#include "SimpleSerialization.h"

class LedStatus : public SerializationData {
public:
    int getDataSize();
    void readData(SerializationInputStream& input);
    void writeData(SerializationOutputStream& output);
    long getStatus() { return status; };
    void setStatus(long status) { this->status = status; };
private:
    long status;
};

#endif	/* _LEDSTATUS_H */
