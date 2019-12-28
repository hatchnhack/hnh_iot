#include <ESP8266WiFi.h> 
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

String apiKey = "<Write API Key>";

const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");  

}
int F1=0;
int F2=0;
void loop() {
  // Wait a few seconds between measurements.

  if (client.connect(server,80)) {
    String postStr = apiKey;
     postStr +="&field1=";
     postStr += String(F1);
     postStr +="&field2=";
     postStr += String(F2);     
     postStr += "\r\n\r\n";
  
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);
  }
  client.stop();
  delay(12000);
  if(F1>200){
    F1 = 0;
  } else {
    F1++;
  }
  if(F2>200){
    F2 = 0;
  } else {
    F2 += 2;
  }
}
