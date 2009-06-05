/*
 * This is the Timer class whose instance (object) is going to be deserialized
 * from the data that was sent via the serial connection.
 * NOTE that unlike in the other examples the preamble and the postamble are
 * set in the constructor. This makes a serialized object unique and thus
 * identifiable by the serial reader.
 */

import jaron.simpleserialization.*;

public class Timer extends SerializationData {
  private int hours;
  private int minutes;
  private int seconds;
  
  public Timer() {
    setPreamble(11223344);  // just random values to
    setPostamble(44332211); // identify the object
  }

  public int getHours() {
    return hours;
  }

  public int getMinutes() {
    return minutes;
  }

  public int getSeconds() {
    return seconds;
  }

  public int getDataSize() {
    int dataSize = SerializationTypes.SIZEOF_STRING; // hours
    dataSize += SerializationTypes.SIZEOF_STRING;    // minutes
    dataSize += SerializationTypes.SIZEOF_STRING;    // seconds
    return dataSize;
  }

  public void readData(SerializationInputStream input) {
      hours = input.readInteger();
      minutes = input.readInteger();
      seconds = input.readInteger();
  }

  public void writeData(SerializationOutputStream output) {
    output.writeInteger(hours);
    output.writeInteger(minutes);
    output.writeInteger(seconds);
  }
}
