/*
 * This sketch keeps all functions and networks 
 */

#include "index.h"
#include "panel.h"

//Create your own thing name
const String dweetThingName = "hdelei-xmas-tree";

//Connect to wifi that first matches one of the WIFI_REPO and print status to serial out
//Returns true if wifi is sucessfuly connected, else returns false
bool connectWifi(){  
  for (int i = 0; i <= ROWS -1; i++){        
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_REPO[0][i]);
    
    WiFi.begin(WIFI_REPO[0][i], WIFI_REPO[1][i]);     
    
    int count = 0;
    while (WiFi.status() != WL_CONNECTED) {
      if (count >= 80){ //wait about 40 seconds to connect i-th wifi on list 
        Serial.println();
        Serial.print(WIFI_REPO[0][i]);
        Serial.print(" Not reached...");
        break;
      }
      
      //digitalWrite(RED_PIN, HIGH);
      delay(250);
      Serial.print(".");
      //digitalWrite(RED_PIN, LOW);
      delay(250);
      count += 1;
    }
    if (WiFi.status() == WL_CONNECTED){ //Stop loop      
      Serial.println("");
      Serial.println("WiFi connected");
      return true;     
    }    
  }   
  return false;  
}

//List networks for debugging pourposes
void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }
  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");    
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.println();
    Serial.flush();
  }
}

void postToDweet(IPAddress ip, int pinZeroStatus, int pinTwoStatus){
  //Client instance to dweet.io
  WiFiClient client;
  char dweet[] = "www.dweet.io"; 
  
  String ipStr = ip.toString();
  String post = "POST /dweet/for/";  
  post.concat(dweetThingName);
  post.concat("?IP=");
  post.concat(ipStr);  
  post.concat("&status[pin_0]=");
  post.concat(pinZeroStatus);
  post.concat("&status[pin_2]=");
  post.concat(pinTwoStatus);   
    
  if (client.connect(dweet, 80)){                  
      client.println(post);
      client.println("HOST: www.dweet.io");
      client.println("Connection: close");
      client.println();      
    }
}

//format responses
String formatJson(int pZeroStat, int pTwoStat){   
    String json = ""; 
    String pzs = (pZeroStat == 1) ? "on":"off";
    String pts = (pTwoStat == 1) ? "on":"off";
    json.concat("{\"status\":{\"pin_0\":\"");        
    json.concat(pzs);
    json.concat("\",\"pin_2\":\"");
    json.concat(pts);
    json.concat("\"}}");    
    return json;
  }

void handleGPIO() {
  if (!server.hasArg("gpio_0") && !server.hasArg("gpio_2"))
    sendResponse("text/plain", "{\"error\":\"no_arg\"}");      
  
  String key = server.argName(0);
  String value = server.arg(0);
  int pin = -1;  
  int state = LOW; 
  
  if(key == "gpio_0")
    pin = 0;      
  else if(key == "gpio_2")
    pin = 2;
  else
    sendResponse("text/plain", "{\"error\":\"invalid_gpio\"}");

  if(value == "on")
    state = HIGH;       
  else if(value == "off")
    state = LOW;
  else
    sendResponse("text/plain", "{\"error\":\"invalid_value\"}");

  digitalWrite(pin, state);
  
  if(pin == 0)  
    pinZeroStatus = state;
  else
    pinTwoStatus = state;
      
  sendResponse("text/plain", formatJson(pinZeroStatus, pinTwoStatus));  
  postToDweet(WiFi.localIP(), pinZeroStatus, pinTwoStatus);
}

void handleStatus(){
  sendResponse("text/plain", formatJson(pinZeroStatus, pinTwoStatus));
}

void handleIndexPage(){
  sendResponse("text/html", MAIN_page);
}

void handlePanelPage(){
  sendResponse("text/html", PANEL_page);
}

void handleSetWifi(){
  String ssid = server.arg(0);
  String password = server.arg(1);
  String message = "{\"*ken*\":\"#ryu#\"}";
  message.replace("*ken*", ssid);
  message.replace("#ryu#", password);
  sendResponse("text/plain", message);
}

void handleNotFound(){
  server.send(404, "text/plain", "Error 404: Page Not Found");
}

void sendResponse(String type, String message){
  server.send(200, type, message);
}

void startServer(){  
    server.on("/", handleIndexPage);    
    server.on("/status", handleStatus);
    server.on("/panel", handlePanelPage);
    server.on("/set", handleGPIO);
    server.on("/setwifi", handleSetWifi);
    server.onNotFound(handleNotFound);
    
    server.begin();
    Serial.println("Server started");
}

