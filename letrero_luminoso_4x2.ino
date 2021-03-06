#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 2;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "MICAS DE CRISTAL $25";
int wait = 60; // In milliseconds

int spacer = 8;
int width = 5 + spacer; // The font width is 5 pixels

void setup() {

  matrix.setIntensity(7); // Use a value between 0 and 15 for brightness

// Adjust to your own needs
  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 1, 0); // The second display is at <1, 0>
  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>
  matrix.setPosition(4, 3, 1); // The first display is at <0, 0>
  matrix.setPosition(5, 2, 1); // The second display is at <1, 0>
  matrix.setPosition(6, 1, 1); // The third display is at <2, 0>
  matrix.setPosition(7, 0, 1); // And the last display is at <3, 0>
//  ...

  matrix.setRotation(0, 1);  
  matrix.setRotation(1, 1);  
  matrix.setRotation(2, 1);  
  matrix.setRotation(3, 1);  
  matrix.setRotation(4, 3);  
  matrix.setRotation(5, 3);  
  matrix.setRotation(6, 3);  
  matrix.setRotation(7, 3);  
}

void loop() {

  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 12) / 2; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 2);
      }

      letter--;
      x -= width;
    }

    matrix.write(); // Send bitmap to display

    delay(wait);
  }
}
