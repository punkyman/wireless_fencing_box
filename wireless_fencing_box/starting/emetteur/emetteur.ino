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


#define CE_PIN   14
#define CSN_PIN 13

#define ID_PIN 12

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe_left = 0x0000DEADBEEF; // Define the transmit pipe
const uint64_t pipe_right = 0x0000BEEFDEAD; // Define the transmit pipe

bool is_left = false;

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int joystick[2];  // 2 element array holding Joystick readings

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  pinMode(ID_PIN,INPUT);
  delay(1000);
  
  
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  
  if(digitalRead(ID_PIN) > 512)
  {
	  is_left = true;
		radio.openWritingPipe(pipe_left);
  }
	else
		radio.openWritingPipe(pipe_right);
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
	int value;
	
	if(is_left)
		value = 1;
	else
		value = 2;
	
	radio.write(&value, sizeof(value));
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/

//NONE
//*********( THE END )***********
