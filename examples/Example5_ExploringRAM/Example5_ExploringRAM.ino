/*
SparkFun TFT LCD 1.8" 128x160 using HyperDisplay
Example5 Exploring RAM

This example is not really going to help understand how to use the TFT display or HyperDisplay library. 
However it is a neat little exploration for the curious!

*Note* Because of the memory requirements of this example it cannot be run on an Arduino Uno or other 
AtMega 328 based board. Consider using a SAMD21 or Teensy board instead.

Arduino Pin    ->   Breakout Pin
--------------------------------
GND           ->    GND
5V            ->    3V3-5V5   * Note: connect this pin to the voltage level that your microcontroller's IO operates at (from 3.3V to 5.5V)
3             ->    PWM
13            ->    SCLK
11            ->    MOSI
6             ->    D/C
5             ->    LCD CS

Author: Owen Lyke
Modified: 1/29/19
This software is open source. Use it how you like, just don't hurt people.

*/
#include "HyperDisplay_KWH018ST01_4WSPI.h" // Click here to get the library: http://librarymanager/All#SparkFun_HyperDisplay_KWH018ST01_4WSPI
                                           // Click here to get the mid-level library: http://librarymanager/All#SparkFun_HyperDisplay_ILI9163C
                                           // Click here to get HyperDisplay (top level): http://librarymanager/All#SparkFun_HyperDisplay

#define SERIAL_PORT Serial    // Allows users to easily change target serial port (e.g. SAMD21's SerialUSB)

#define PWM_PIN 3             // Pin definitions
#define CS_PIN 5
#define DC_PIN 6
#define SPI_PORT SPI
#define SPI_SPEED 32000000    // Requests host uC to use the fastest possible SPI speed up to 32 MHz

KWH018ST01_4WSPI myTFT;       

ILI9163C_color_18_t defaultColor;

void setup() {
  SERIAL_PORT.begin(9600);
  SERIAL_PORT.println("Example2 HyperDisplay : SparkFun TFT LCD 1.8in Breakout");

  myTFT.begin(DC_PIN, CS_PIN, PWM_PIN, SPI_PORT, SPI_SPEED);  // This is a non-hyperdisplay function, but it is required to make the display work
  myTFT.clearDisplay();                                       // clearDisplay is also not pat of hyperdisplay, but we will use it here for simplicity

  defaultColor = myTFT.rgbTo18b( 255, 255, 255 );


  // In Example4 we demonstrated how to associate memory with a window. Let's use that method in a hacky kind of way to visualize our uC's RAM!
  void* addr = (void*)&defaultColor; // Choosing a statically allocated variable is a good way to guess the approximate beginning of RAM
  uint32_t count = 0;


  // At your option try setting some memory values to see if you can recognize them later...  
  for(uint32_t indi = 0; indi < 3000; indi++){        // And to be clear - this is not considered a good coding practice ususally!
    *(((uint8_t*)addr) + 0x8000 + 3*indi + 0) = 0x00;     
    *(((uint8_t*)addr) + 0x8000 + 3*indi + 1) = 0xFF; 
    *(((uint8_t*)addr) + 0x8000 + 3*indi + 2) = 0x00; 
  }


  while(1){
      myTFT.setCurrentWindowMemory((color_t)addr, 128*160); 
      myTFT.show();

      count++;
      addr = (void*)(((uint8_t*)addr)+160*sizeof(ILI9163C_color_18_t)); // Cast to uint8_t pointer to increment the start address

      SERIAL_PORT.println(count);
  }

  // On a Teensy3.6 this quit after 410 iterations. 
  // That is roughly correct for the RAM size on the Teensy3.6.
  // Each pixel is 3 bytes. We show 128*160 pixels = 61 kilobytes for each screen.
  // Each count adds 160 pixels to the "consumed" RAM, or 480 bytes. For 410 counts 
  // we are using an additional 410*480 = 196.8 kilobytes.
  // Together they sum to 258240 bytes, Arduino says the maximum is 262144 bytes.
  // We might fairly assume that the remaining 3904 bytes are located before 'defaultColor' in RAM 
  // and are part of the Arduino and HyperDisplay overheads
}

void loop() {

}
