# sentitweet-ioT
Sentitweet is an artwork created by Marion Schneider at UQAM.  It consists of a Twitter bot searching with the Query "This artwork is" and analysing the related sentiment of each Tweet. It then displays a real-time value on a TFT screen and prints out some of the tweets on a Thermal Printer via WIFI connected ESP8266 (wemos).

Here is the code for the Hardwarde ioT part of the project. Using Arduino code on a Wemos Mini at 115200 upload speed. I assume that you know how to connect your Wemos or any other ESP8266 chip to Arduino. Otherwise you will have to include the ESP8266 library that can be selected and downloaded in the software itself.

I uploaded my main code, that I'm currently using and some parts of it in case you only want to try to print with esp8266, get the TFT screen to give values, or parse Json Data from Thingspeak.

For the printer I used the library from Adafruit making only 2 small changes : one for the Baudrate of the printer, in my case needed 9600 instead of 19200 (depends on the printer). And in the library itself, you need to change one line of code ( if using ESP8266/wemos) that I specified in the esp8266 thermal printer code.

https://github.com/adafruit/Adafruit-Thermal-Printer-Library

For the screen also the Libary from Adafruit. ( the pin numbers are in the thermal printer esp8266 code )

https://github.com/adafruit/Adafruit-ST7735-Library

Parsing Data from Thingspeak Json format url to Arduino is done using ArduinoJson Libary, you will need to download it.

https://github.com/bblanchon/ArduinoJson

The twitter account related to the artwork is @sentitweeet.

Material used for the project: TFT 1.8 screen, Adafruit Thermal Printer Guts, Wemos Mini, wires, a breadbord, a 7.5v 2.5 Amp DC adaptor ( for the printer).

You can get the code for the node.js app part of the project in another repository called sentitweet.

Have fun !!! 
