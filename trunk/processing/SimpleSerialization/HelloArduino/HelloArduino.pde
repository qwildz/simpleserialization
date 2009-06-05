/*
 * Replace "COM4" with the serial port your Arduino is connected to.
 * Replace 115200 with the baud rate your Arduino communicates.
 *
 * A very simple example that receives a string from the Arduino containing the
 * message "Hello Arduino!". Have a look the according Arduino example to see
 * how the message is sent.
 */
 
import jaron.simpleserialization.*;
import processing.serial.*;

String serialPort = "COM4";
int connectionSpeed = 115200;

void setup() {
  // The Processing setup
  size(350, 200);
  frame.setTitle("The message is displayed in the console");

  // This is the object where the message will be stored in
  Message message = new Message();

  // The listener prints out the message received from the Arduiono
  MessageListener listener = new MessageListener();
  message.addListener(listener);
  
  // Initialize the serialization
  SerializationSerialConnection conn = new SerializationSerialConnection(this, serialPort, connectionSpeed);
  conn.addDeserializableData(message);
}

void draw() {
}

