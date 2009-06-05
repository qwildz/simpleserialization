/*
 * This is the declaration of the Timer class whose instance (object) is going
 * to be serialized and sent via the serial connection.
 * In its constructor method this class defines new values for the preamble and
 * the postamble. That makes the instances of this class distinguishable from
 * any other objects that are serialized.
 */

#ifndef _TIMER_H
#define	_TIMER_H

#include "SimpleSerialization.h"

class Timer : public SerializationData {
public:
    Timer();
    int getDataSize();
    void readData(SerializationInputStream& input);
    void writeData(SerializationOutputStream& output);
    void setHours(long hours) { this->hours = hours; };
    void setMinutes(long minutes) { this->minutes = minutes; };
    void setSeconds(long seconds) { this->seconds = seconds; };
private:
    long hours;
    long minutes;
    long seconds;
};

#endif	/* _TIMER_H */
