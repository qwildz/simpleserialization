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
  frame.setTitle("The messages are displayed in the console");

  // This is the object where the timer values will be stored in
  Timer myTimer = new Timer();

  // This is the object where the message will be stored in
  Message message = new Message();

  // The listener prints out the message received from the Arduiono
  DataListener listener = new DataListener();
  myTimer.addListener(listener);
  message.addListener(listener);
  
  // Initialize the serialization
  SerializationSerialConnection conn = new SerializationSerialConnection(this, serialPort, connectionSpeed);
  conn.addDeserializableData(myTimer);
  conn.addDeserializableData(message);
}

void draw() {
}

