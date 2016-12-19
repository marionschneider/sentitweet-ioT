#include <ESP8266WiFi.h> // for wemos or any ESP8266 board
#include <ArduinoJson.h> // to parse Json data coming in the terminal



const char* ssid     = "YOUR WIFI NAME";      // SSID of local network
const char* password = "YOUR WIFI PASSWORD";   // Password on local network
String APIKEY = "YOUR THINGSPEAK STRING API KEY"; // necessary if your Api isn't public ( copy your read API key for Thingspeak connection )



WiFiClient client;
char servername[]="api.thingspeak.com";  // server we will connect to
String result;

int  counter = 5; // 60 = Get new data every 10 min

String tweetText =""; // string var to store your tweet
String nothing = "";


void setup() {
  Serial.begin(115200); // comunication with your serial monitor
  
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

  }

  Serial.println("Connected");
  delay(1000);

}

void loop() {
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
}

void getData() //client function to send/receive GET request data.
{
  if (client.connect(servername, 80)) {  //starts client connection, checks for connection
    client.println("GET /channels/195890/fields/2.json?results=1");
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
 //imprimer
  Serial.print(textedutweet); // finally the tweet value arriving as a beautifull string !!
}



void displayGettingData()
{
  Serial.print("Getting data"); 
}
