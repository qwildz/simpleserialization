package jaron.simpleserialization;
import java.io.ByteArrayInputStream;

/**
 * The <code>SerializationInputStream</code> class implements the functionality
 * to convert simple data types like integers, floats and strings into serilized
 * data.
 *   
 * @author      jarontec gmail com
 * @version     1.0
 * @since       1.0
 */
public class SerializationInputStream extends ByteArrayInputStream {
  public SerializationInputStream(byte[] buffer) {
    super(buffer);
  }

  public SerializationInputStream(byte[] buf, int offset, int length) {
    super(buf, offset, length);
  }
  
  public int readInteger() {
    byte b[] = new byte[4];
    b[0] = (byte )read();
    b[1] = (byte )read();
    b[2] = (byte )read();
    b[3] = (byte )read();
    return SerializationTypes.bytesToInteger(b);
  }
  
  public float readFloat() {
    return Float.intBitsToFloat(readInteger());
  }
  
  public String readString() {
    int len = readInteger(); // get string length first
    StringBuffer s = new StringBuffer();
    for (int i=0; i<len; ++i) {
      s.append((char )read());
    }
    return s.toString();
  }

}
