/*
 * This is the LedStatus class whose instance (object) is going to be serialized
 * and sent via the serial connection.
 */

import jaron.simpleserialization.*;

public class LedStatus extends SerializationData {
  private int status = 0;

  public int getStatus() {
    return status;
  }

  public void setStatus(int status) {
    this.status = status;
  }

  public int getDataSize() {
    return SerializationTypes.SIZEOF_INTEGER;
  }

  public void readData(SerializationInputStream input) {
      status = input.readInteger();
  }

  public void writeData(SerializationOutputStream output) {
    output.writeInteger(status);
  }
}
