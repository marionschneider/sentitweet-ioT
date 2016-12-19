
********///////// ESP8266 - ADAFRUIT THERMAL PRINTER *********///////////////

/*Please note that the printer needs a lot of power, there is no way it will
function correctly if you don't plug it to the wall (even the guts version)
a 5V 2,5 amp was not enough for me,  had to upgrade to 7,5V 2,5 amp*/


///IN ORDER FOR THE ADAFRUIT_THERMAL TO WORK WITH ESP8266 (wemos) YOU HAVE TO// 
//// CHANGE A LINE IN THE LIBRARY IN adafruit_thermal.cpp replace ////////////
//while((long)(micros() - resumeTime) < 0L);//////////////////////////////////
// WITH delay(10) > THAN CLOSE ARDUINO AND LOAD YOUR SKETCH AGAIN ////////////


#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include "adalogo.h"
#include "adaqrcode.h"
#define TX_PIN 12 // RX on printer // hardware pin D6 for Wemos
#define RX_PIN 13 // TX on printer // hardware pin D7 for Wemos

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);  

void setup() {

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(9600);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
   printTweet();
}

void printTweet () {

 // Test more styles
  printer.boldOn();
  printer.println(F("--"));
  printer.boldOff();

  delay(20000);
  printer.println(F("RT @McKelvie: If you're using art from comics to illustrate your list of writers in comics, credit the artists, yeah?"));
  printer.timeoutSet(2000);
  printer.setLineHeight(); // Reset to default
  printer.justify('L');
  
}

void loop() {

  printer.sleep();
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); 
         
}
