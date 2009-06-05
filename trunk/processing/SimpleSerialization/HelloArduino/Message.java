/*
 * This is the Message class whose instance (object) is going to be deserialized
 * from the data that was sent via the serial connection.
 */

import jaron.simpleserialization.*;

public class Message extends SerializationData {
  private String message = "";

  public String getMessage() {
    return message;
  }

  public void setMessaage(String message) {
    this.message = message;
  }

  public int getDataSize() {
    return (SerializationTypes.SIZEOF_STRING + message.length());
  }

  public void readData(SerializationInputStream input) {
      message = input.readString();
  }

  public void writeData(SerializationOutputStream output) {
    output.writeString(message);
  }
}
