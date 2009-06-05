/*
 * This is the DataListener class that provides the functionality to print
 * the incoming message and the Arduino timer data to the console.
 */
import jaron.simpleserialization.*;

public class DataListener implements SerializationDataEventListener {
  public void dataUpdate(SerializationData data) {
    if (data.getClass() == Timer.class) {
      int hours = ((Timer)data).getHours();
      int minutes = ((Timer)data).getMinutes();
      int seconds = ((Timer)data).getSeconds();
      System.out.println(String.format("Arduino timer %02d:%02d:%02d", hours, minutes, seconds));
    }
    else if (data.getClass() == Message.class) {
      System.out.println(((Message)data).getMessage() + ": " + ((Message)data).getPI());
    }
  }
}
