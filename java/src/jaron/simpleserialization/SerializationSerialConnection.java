package jaron.simpleserialization;
import java.util.ArrayList;

import processing.core.PApplet;
import processing.serial.Serial;

/**
 * The <code>SerializationSerialConnection</code> class provides the functionality
 * to establish a serial connection and send and receive serialized data.
 *   
 * @author      jarontec gmail com
 * @version     1.0
 * @since       1.0
 */
public class SerializationSerialConnection extends Thread implements Runnable {
  private static final float DEFAULT_UPDATE_FREQUENCY = 10;

  private ArrayList<SerializationSerialReader> readers = new ArrayList<SerializationSerialReader>();
  private Serial serial;
  
  public SerializationSerialConnection(PApplet applet, String port, int speed) {
    serial = new Serial(applet, port, speed);
    setDaemon(true);
    start();
  }
  
  public void addDeserializableData(SerializationData data) {
    SerializationSerialReader reader = new SerializationSerialReader(data);
    addReader(reader);
  }
  
  public void addReader(SerializationSerialReader reader) {
    readers.add(reader);
  }

  @Override
  public void run() {
    while(true) {
      while(serial.available() > 0) {
        byte b = (byte )serial.read();
        for (SerializationSerialReader reader : readers) { 
          reader.processData(b);
        }
      }
      try { sleep((long )(1000 / DEFAULT_UPDATE_FREQUENCY)); } catch(InterruptedException e) {} 
    }
  }
  
  public void write(SerializationData data) {
    SerializationOutputStream output = new SerializationOutputStream(data.getDataSize());
    data.write(output);                 // serialize data and write it to a buffer
    serial.write(output.toByteArray()); // write the buffer to the serial interface
  }
}
