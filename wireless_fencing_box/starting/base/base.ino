/* YourDuinoStarter Example: nRF24L01 Receive Joystick values

 - WHAT IT DOES: Receives data from another transceiver with
   2 Analog values from a Joystick or 2 Potentiometers
   Displays received values on Serial Monitor
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   
 - V1.00 11/26/13
   Based on examples at http://www.bajdi.com/
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
/*-----( Declare Constants and Pin Numbers )-----*/


#define CE_PIN  9
#define CSN_PIN 10

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe_left = 0x0000DEADBEEF; // Define the transmit pipe
const uint64_t pipe_right = 0x0000BEEFDEAD; // Define the transmit pipe

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();

  radio.openReadingPipe(1, pipe_left);
  radio.openReadingPipe(2, pipe_right);

  radio.startListening();
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
    uint8_t pipe;
    int value=666;
	if(radio.available(&pipe))
    {
      bool result = radio.read(&value, sizeof(value));
      if(pipe == 1)
        Serial.write("received from left :");
       else if(pipe == 2)
        Serial.write("received from right :");
      if(result) Serial.write(value);
      Serial.write("\n");
    }
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/

//NONE
//*********( THE END )***********
