import controlP5.*; //import ControlP5 library
import processing.serial.*;

Serial port;

ControlP5 cp5; //create ControlP5 object
PFont font;

void setup(){ //same as arduino program

  size(1920, 1080);    //window size, (width, height)
  
  printArray(Serial.list());   //prints all available serial ports
  
  port = new Serial(this, "COM7", 9600);  //change depending on where port is connected
  
  //lets add buton to empty window
  
  cp5 = new ControlP5(this);
  font = createFont("calibri light bold", 20);    // custom fonts for buttons and title
  
  cp5.addButton("up")     //"up" is the name of button
    .setPosition(850, 150)  //x and y coordinates of upper left corner of button
    .setSize(200, 200)      //(width, height)
    .setFont(font)
  ;   

  cp5.addButton("left")     //"left" is the name of button
    .setPosition(600, 325)  //x and y coordinates of upper left corner of button
    .setSize(200, 200)      //(width, height)
    .setFont(font)
  ;

  cp5.addButton("right")     //"right" is the name of button
    .setPosition(1100, 325)  //x and y coordinates of upper left corner of button
    .setSize(200, 200)      //(width, height)
    .setFont(font)
  ;
  
  cp5.addButton("down")     //"down" is the name of button
    .setPosition(850, 500)  //x and y coordinates of upper left corner of button
    .setSize(200, 200)      //(width, height)
    .setFont(font)
  ;
  
  cp5.addButton("ColorSensor")
    .setPosition(850, 800)
    .setSize(200, 200)
    .setFont(font)
  ;
}

void draw(){  //same as loop in arduino

  background(0, 0, 0); // background color of window (r, g, b) or (0 to 255)
  
  //window title
  fill(255, 255, 255);               //text color (r, g, b)
  textFont(font);
  textSize(48);
  text("ROVER CONTROL", 750, 75);  // ("text", x coordinate, y coordinate)
}

//lets add some functions to our buttons
//so when you press any button, it sends perticular char over serial port

void up(){
  port.write('w');
}

void left(){
  port.write('a');
}

void right(){
  port.write('d');
}

void down(){
  port.write('s');
}

void ColorSensor(){
  port.write('c');
}
