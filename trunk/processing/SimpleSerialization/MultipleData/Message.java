/*
 * This is the Message class whose instance (object) is going to be deserialized
 * from the data that was sent via the serial connection.
 */

import jaron.simpleserialization.*;

public class Message extends SerializationData {
  private String message = "";
  private float pi;

  public String getMessage() {
    return message;
  }

  public void setMessaage(String message) {
    this.message = message;
  }
  
  public float getPI() {
    return pi;
  }
  
  public void setPI(float pi) {
    this.pi = pi;
  }

  public int getDataSize() {
    int size = SerializationTypes.SIZEOF_STRING + message.length();
    size += SerializationTypes.SIZEOF_FLOAT;
    return size;
  }

  public void readData(SerializationInputStream input) {
      message = input.readString();
      pi = input.readFloat();
  }

  public void writeData(SerializationOutputStream output) {
    output.writeString(message);
    output.writeFloat(pi);
  }
}
