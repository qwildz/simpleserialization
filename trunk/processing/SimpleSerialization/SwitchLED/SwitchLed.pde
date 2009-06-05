/*
 * Replace "COM4" with the serial port your Arduino is connected to.
 * Replace 115200 with the baud rate your Arduino communicates.
 *
 * A very simple example that sends an integer value to the Arduino when the
 * mouse is pressed or released. The Arduino then turns an LED on or off.
 * Have a look at the Arduino SwitchLed example to see how the value is received.
 */

import jaron.simpleserialization.*;
import processing.serial.*;

String serialPort = "COM4";
int connectionSpeed = 115200;
SerializationSerialConnection conn;

void setup() {
  // The Processing setup
  size(350, 200);
  frame.setTitle("Click into this window to switch the LED on");
  
  // Initialize the serialization
  conn = new SerializationSerialConnection(this, serialPort, connectionSpeed);
}

void draw() {
}

void mousePressed() {
  // If the mouse is pressed then send 1 to the Arduino
  LedStatus ledStatus = new LedStatus();
  ledStatus.setStatus(1);
  conn.write(ledStatus);
}

void mouseReleased() {
  // If the mouse is released then send 0 to the Arduino
  LedStatus ledStatus = new LedStatus();
  ledStatus.setStatus(0);
  conn.write(ledStatus);
}

