
#include "ThingSpeak.h"
#include <SPI.h>
#include <ESP8266WiFi.h>

///////////////////////////////////////////////////////////////////////// setup ecran
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     15
#define TFT_RST    0  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     5

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 3   // set these to be whatever pins you like!
#define TFT_MOSI 4   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
///////////////////////////////////////////////////////////////////////////////////////////

char ssid[] = "BELL402"; // your network SSID (name)
char pass[] = "32F6A795"; // your network password

WiFiClient client;

unsigned long myChannelNumber = 195890;  // your channel number
const char * myReadAPIKey = "MDUNYG2CBBKSNBGO";  // your read api key

void setup() {
Serial.begin(9600);
WiFi.begin(ssid, pass);
ThingSpeak.begin(client);
//
tft.initR(INITR_BLACKTAB);
 Serial.println("Initialized");

 uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  //delay(500);
  tft.setRotation(3);

  

  Serial.println("done");
  //delay(1500);
}

void loop() {
float valeur = ThingSpeak.readFloatField(myChannelNumber, 1);  // reads a float, in this case a temperature
//float tweetext = ThingSpeak.readStringField(myChannelNumber, 2, myReadAPIKey);

testdrawtext();

//Serial.print("Valeur de l'oeuvre: ");
//Serial.print(valeur);
//Serial.println(" !");
//Serial.print(tweetext);
//delay(50);
////
//tft.invertDisplay(false);
  delay(1500);
   tft.fillRect(0, 50, 500, 30,ST7735_BLACK);
    
   
    //tft.setCursor(20, 60);
    
   // tft.println(valeur);
   
}

void testdrawtext() {
  //tft.fillScreen(ST7735_BLACK);
  tft.setCursor(20, 10);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(false);
    tft.setTextSize(1);
  tft.println("la valeur de");
  tft.setCursor(20, 20);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(false);
  tft.setTextSize(1);
  tft.println("l'oeuvre est : ");
  
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.setTextWrap(false);
  tft.setCursor(20, 60);
  float valeur = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey); 
  
  tft.println(valeur);

  
  
}

