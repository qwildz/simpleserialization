/*
 * This is the MessageListener class that provides the functionality to print
 * the incoming message to the console.
 */

import jaron.simpleserialization.*;

public class MessageListener implements SerializationDataEventListener {
  public void dataUpdate(SerializationData data) {
    System.out.println(((Message)data).getMessage());
  }
}
