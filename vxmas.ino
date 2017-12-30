/*
    This sketch control Christmas Tree lights
    Connect to predefined wifi and act as simple webserver to control GPIO's
    The server will set a GPIO pin depending on the request
      http://server_ip/ will show web interface
      http://server_ip/set?gpio_0=on will set the GPIO0 high
      http://server_ip/set?gpio_0=off will set the GPIO0 low
      http://server_ip/set?gpio_2=on will set the GPIO2 high
      http://server_ip/set?gpio_2=off will set the GPIO2 low
      http://server_ip/status will show last status of lights
      http://server_ip/panel will show wifi panel interface

      (server_ip) is the IP address of the ESP8266 module, will be
      printed to Serial when the module is connected.

    Author: Vanderlei
    Versions:
      v 2.0 25/12/2017 - Added ESP8266WebServer library, refactored all request functions
      and was created panel page to change wifi SSID and Password. Obs.: panel not functional yet

      v 1.1 23/12/2017 - Log IP address to dweet.io at https://dweet.io/follow/hdelei-xmas-tree
        and split in 3 .ino files (vxmas, assids, auxiliar) and 1 .h file (index)
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const int PIN_2 = 2;
const int PIN_0 = 0;
int pinZeroStatus = LOW;
int pinTwoStatus = LOW;

unsigned long prevMillis = 0;
int interval = 3600000;//60 minutes

// Create an instance of the server
// specify the port to listen on as an argument
ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  // prepare GPIO's
  pinMode(PIN_0, OUTPUT);
  digitalWrite(PIN_0, LOW);
  pinMode(PIN_2, OUTPUT);
  digitalWrite(PIN_2, LOW);

  //List available networks. Only for debugging
  listNetworks();

  WiFi.mode(WIFI_STA);

  // Connect to WiFi network
  bool isConnected = connectWifi();

  // Start the server
  if (isConnected) {
    // Print the IP address
    Serial.println(WiFi.localIP());

    //Start the webserver
    startServer();

    // Post IP to dweet.io
    postToDweet(WiFi.localIP(), pinZeroStatus, pinTwoStatus);
  }
}

void loop() {

  /*Check if wifi is connected
     If not, turn on AP mode
  */
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - prevMillis) >= interval ) {
    prevMillis = currentMillis;

    //If there's no connection, turn AP mode on
    //to set wifi client SSID and password
    if (WiFi.status() != WL_CONNECTED) {
      if (!connectWifi()) {
        WiFi.mode(WIFI_AP_STA);
        Serial.println("Wifi not reached. Access Point running");
      }
    }
  }

  server.handleClient();

}

