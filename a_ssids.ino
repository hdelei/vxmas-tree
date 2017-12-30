/*
 * This sketch keeps SSID's and passwords for main_sketch
 */

 //keeps the sizes of wifi repository for easy declaration
const int COLS = 2;
const int ROWS = 3;

//Wifi SSID and PASSWORD repository
const char* WIFI_REPO[COLS][ROWS] = {
  {"SSID1",     "SSID2",     "SSID3"},
  {"PASSWORD1", "PASSWORD2", "PASSWORD3"}
};
