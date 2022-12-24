#include <Arduino.h>
#line 1 "c:\\Users\\Cobbie\\git\\arduino-projects\\PixelLED\\PixelLED.ino"
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 6
#define NUMPIXELS 8
#define DELAYVAL 500
Adafruit_NeoPixel pixels(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int regulate_pin = A0;
int x_axis_pin = A1;
int y_axis_pin = A2;
int button_pin = A3;
int reg_val, reg_val_map, x, y, x_map, y_map;
int button_val;
int index = 0;
byte count;

bool isRunning = true;
bool buttonPressed = false;

uint32_t color;


String logging;

#line 25 "c:\\Users\\Cobbie\\git\\arduino-projects\\PixelLED\\PixelLED.ino"
void setup();
#line 31 "c:\\Users\\Cobbie\\git\\arduino-projects\\PixelLED\\PixelLED.ino"
void loop();
#line 83 "c:\\Users\\Cobbie\\git\\arduino-projects\\PixelLED\\PixelLED.ino"
void displayBinary(byte n);
#line 25 "c:\\Users\\Cobbie\\git\\arduino-projects\\PixelLED\\PixelLED.ino"
void setup() {
  Serial.begin(9600);
  pixels.begin();
  count = 0;
}

void loop() {
  //value read and logging stuff  
  logging = "\nLOG index " + (String)index+ "\n";
  logging += "Status of running bool: " + (String)isRunning + "\n";
  logging += "Status of buttonPressed bool: " + (String)buttonPressed + "\n";
  x = analogRead(x_axis_pin);
  y = analogRead(y_axis_pin);
  reg_val = analogRead(regulate_pin);
  button_val = analogRead(button_pin);
  logging += "Position of regulate: " + (String)reg_val+"\n";
  logging += "Position of button: " + (String)x + "," + (String)y +"\n";
  logging += "ButtonPressed?: " + (String)button_val + "\n";
  //Serial.print(logging);
  
  //pixel stuff

  x_map = map(x,0,1023,0,255);
  y_map = map(y,0,1023,0,255);
  int color_one = x % 255;
  int color_two = (y-x) % 255;
  int color_three = (y+x) % 255; 
  reg_val_map = map(reg_val, 0, 1023, 0, 255);
  color = pixels.Color(0,abs(reg_val_map),abs(reg_val_map));


  //End of loop stuff
  index++;
  displayBinary(count++);
  delay(500);
  
  /*if (isRunning) {
    reg_val = analogRead(regulate_pin); // [0,1023]
    reg_val_map = map(reg_val, 0, 1023, 0, 255);
    x = analogRead(x_axis_pin);
    y = analogRead(y_axis_pin);
    x_map = map(x, 0,1023,0,80);
    y_map = map(y, 0,1023,0,80);
    if (index % 3 == 0){
      pixels.setPixelColor(index%8,pixels.Color((int) (x_map * reg_val_map)/ 100 % 255, (int) (y_map * reg_val_map)/ 100 % 255,(int) ((y_map * reg_val_map)/ 100 + (x_map * reg_val_map)/ 100% 255)));
    }
    else if (index % 3 == 1){
      pixels.setPixelColor(index%8,pixels.Color((int) (x_map * reg_val_map)/ 100 % 255, (int) (y_map * reg_val_map)/ 100 % 255,(int) ((y_map * reg_val_map)/ 100 + (x_map * reg_val_map)/ 100% 255)));
    }
    else {
      pixels.setPixelColor(index%8,pixels.Color((int) (x_map * reg_val_map)/ 100 % 255, (int) (y_map * reg_val_map)/ 100 % 255,(int) ((y_map * reg_val_map)/ 100 + (x_map * reg_val_map)/ 100% 255)));
    }
    pixels.show();
    delay(10);
    index++;
  }*/
}

void displayBinary(byte n){
  pixels.clear();
  for (int i = 0; i<8; i++){
    if (n % 2 == 1){
      pixels.setPixelColor(i,color);
    }
    n /= 2;
  }
  pixels.show();
}

