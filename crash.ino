#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ArduinoJson.h>

#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "accident4"
#define IFTTTKEY "csYIPBf1OPQTz49VNYTWzM"
WiFiClient client;
 

const char* ssid = "IOT31";
const char* password = "password";
int ledPin = 13; // GPIO13
int echo = 14;//d5
int crash = 12;//d6
// defines variables
long duration;
int distance;
//bool notification_timer = false;
//WiFiServer server(80);
int buzzer =  15; //d8

int present_condition = 0;

int previous_condition = 0; 


 
void setup() {
   
Serial.begin(115200);
  delay(400); 
 
//  pinMode(ledPin, OUTPUT);
//  pinMode(echo,INPUT);
  pinMode(crash,INPUT);
  digitalWrite(ledPin, LOW);
pinMode(buzzer,OUTPUT); 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
//  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");


  //Send Webook to IFTTT
//  send_webhook(IFTTTEVENT,IFTTTKEY) 
}

bool check = true;
void loop() {



previous_condition= present_condition;

present_condition = digitalRead(D6);  

if (previous_condition != present_condition) {
  Serial.println("Accident Detected");
  digitalWrite(buzzer, LOW) ;
    digitalWrite(ledPin,HIGH);
    if(check == true){
      check = false;
      if (client.connected())
      {
        client.stop();
        }
      
        client.flush();
      
      if (client.connect(HOSTIFTTT,80)) {
          // build the HTTP requestg
          String toSend = "GET /trigger/";
          toSend += EVENTO;
          toSend += "/with/key/";
          toSend += IFTTTKEY;
          toSend += "?value1=";
          toSend += "Softwarica";
          toSend += " HTTP/1.1\r\n";
          toSend += "Host: ";
          toSend += HOSTIFTTT;
          toSend += "\r\n";
          toSend += "Connection: close\r\n\r\n";
          client.print(toSend);
         // delay(5000);
        }
      }
  }  
    else{
     // digitalWrite(ledPin,LOW);
      check = true;
      Serial.println("Accident not Detected");
      digitalWrite(buzzer, HIGH) ;
    }
  
// 
//  delay(500);
 

//led_blink();
'[


}







  
