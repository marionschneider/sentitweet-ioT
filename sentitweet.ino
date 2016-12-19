#include <ESP8266WiFi.h> 
#include <ArduinoJson.h>
#include "ThingSpeak.h"
#include <SPI.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define TX_PIN 2 //D6                            ___ PRINTER
#define RX_PIN 12 //D4
SoftwareSerial mySerial(RX_PIN, TX_PIN); 
Adafruit_Thermal printer(&mySerial); 

#define TFT_CS     15 // D8                       ___ SCREEN
#define TFT_RST    0  // RST
#define TFT_DC     5  // D1
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
#define TFT_SCLK 3   // D5
#define TFT_MOSI 4   // D7

const char* ssid     = "YOUR WIFI NAME";//               ___ WIFI GET
const char* password = "YOUR WIFI PASSWORD"; 

unsigned long myChannelNumber = 195890;  //       ___ THINGSPEAK
const char * myReadAPIKey = "YOUR THINGSPEAK READ API KEY";// ___ READ METHOD (only needed if not public channel)

WiFiClient client; // wifi get
char servername[]="api.thingspeak.com";
String result;

int  counter = 5; // 60 = Get new data every 10 min

String tweetText =""; 
String nothing = "";

void setup() {
  Serial.begin(9600); // might trouble with WIFI get was 115200
  WiFi.begin(ssid, password); // changed both to password
  ThingSpeak.begin(client);
  while (WiFi.status() != WL_CONNECTED) { // from wifi get
  delay(500); //
  }

  mySerial.begin(9600);  // Initialize SoftwareSerial printer
  printer.begin(); 
 

  tft.initR(INITR_BLACKTAB); // screen
  Serial.println("Initialized");
  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  tft.setRotation(3);
  Serial.println("done");
  Serial.println("Connected");
  delay(1000);
  
}
  

void loop() {

  testdrawtext(); //screen
  delay(15000);
  
  
    if(counter == 5) //60 = Get new data every 10 minutes
    {
      counter = 0;// resets the counter if 10 min happened
      displayGettingData(); // writes down the received data
      delay(1000);
      getData(); // loads the data via GET request
      result=""; // clears the last GET result so it can parse the next one and uses less memory
      displayTweet(nothing,tweetText);// displays the parsed result in the serial monitor
 
    }else
    {
      counter++;
      delay(5000); //waits before getting new data
      delay(5000);
    }

  
  printer.sleep(); // printer
  //delay(3000L);  
  printer.wake();
  printer.setDefault(); 

  tft.fillRect(0, 50, 500, 30,ST7735_BLACK);
  
}

void getData() //client function to send/receive GET request data.
{
  if (client.connect(servername, 80)) {  //starts client connection, checks for connection
    client.println("GET /channels/195890/fields/2.json?results=1"); //!! REPLACE 195890 WITH YOUR CHANNEL NUMBER 
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } 
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }

  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
      result = result+c; // adds new data to last data
    }

  client.stop(); //stop client
  result.replace('[', ' '); // new to do it to correctly parse your data
  result.replace(']', ' '); // with ArduinoJson
  Serial.println(result); // shows the received data 

char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';

StaticJsonBuffer<1024> json_buf;

JsonObject &root = json_buf.parseObject(jsonArray);
if (!root.success())
{
  Serial.println("parseObject() failed");
}

String textedutweet = root["feeds"]["field2"]; // path to json data, here feeds.field2

tweetText = textedutweet;
}

void displayTweet(String nothing,String textedutweet)
{

  printer.boldOn();
  printer.println(F("--"));
  printer.boldOff();

  delay(2000);
  printer.println(textedutweet);
  printer.timeoutSet(2000);
  printer.setLineHeight(); // Reset to default
  printer.justify('L');
  Serial.print(textedutweet);
}

void displayGettingData()
{
  Serial.print("Getting data"); 
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






