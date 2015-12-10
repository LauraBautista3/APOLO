import processing.serial.*;
import processing.opengl.*;

int channel1;
int channel2;

Serial myPort; 


void leer ()
{
  while (myPort.available() > 0) {
  String inBuffer = myPort.readString();   
  if (inBuffer != null) {
      println(inBuffer);
    }
  }
}

// Send new DMX channel value to FPGA
//
void setDmxChannel(int channel, int value) {
  // Convert the parameters into a message of the form: 123c45w where 123 is the channel and 45 is the value
  // then send to the FPGA
  //println(value);
  myPort.write( "<" + (channel) + "c" + (value) + "w" );
  leer();
}

// Draw gradient window
//
void drawGradient() {
  // Draw a colour gradient
  beginShape(QUADS);
  fill(0,0,255); vertex(0,0); // Top left BLUE
  fill(255,0,0); vertex(width,0); // Top right RED
  fill(255,255,0); vertex(width,height); // Bottom right RED + GREEN
  fill(0,255,255); vertex(0,height); // Bottom left BLUE + GREEN
  endShape(); 
}  

void setup() {
//  println(Serial.list()); // shows available serial ports on the system
  // Change 0 to select the appropriate port as required.
  String portName = "/dev/ttyUSB0";
  myPort = new Serial(this, portName, 115200);

  size(255,255,OPENGL);  // Create a window
  drawGradient();
}

void draw() {
  channel1 = (255 * mouseX / width); // Use cursor X position to get channel 1 value
  channel2 = (255 * mouseY / height);// Use cursor Y position to get channel 2 value
 // channel1 = hex (channel1);
  //channel2 = hex (channel2);
  setDmxChannel(1, channel1); // Send new channel values to FPGA
  setDmxChannel(2,channel2);
  setDmxChannel(3,255-channel1);
  
  
  // You may have to set other channels. Some lamps have a shutter channel that should be set to 255.
  // Set it here:
  // setDmxChannel(4,255);
  
  delay(80);  // Short pause before repeating
}