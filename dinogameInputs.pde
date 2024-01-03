import processing.serial.*;
Serial myPort;

void setup() {
  size(500,500);
  background(100,60,120);
  myPort = new Serial (this, "COM18", 9600);
  myPort.bufferUntil('\n');
}

void draw(){
  if(mousePressed){
    myPort.write('w');
  }
}
