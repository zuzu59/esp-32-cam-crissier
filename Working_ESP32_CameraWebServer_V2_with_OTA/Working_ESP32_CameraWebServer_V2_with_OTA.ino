#define zVERSION        "zf240909.1923"
#define zHOST           "esp-cam-crissier"        // ATTENTION, tout en minuscule
#define zDSLEEP         0                       // 0 ou 1 !
// #define TIME_TO_SLEEP   120                     // dSleep en secondes 



#include "esp_camera.h"
#include <WiFi.h>
#include <ESPmDNS.h> //Required to compile on Russian 'ArduinoDroid' IDE but not required on Arduino IDE
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


// Secrets pour WIFI
#include "secrets.h"

// OTA WEB server
#include "otaWebServer.h"



/*
 * BOARD SETTINGS
 * 
 * Board type: ESP32 Wrover Module
 * 
 */

// Getting WIFI_SSID and WIFI_PASSWORD from external credentials file
//#include "jtektiot_credentials.h";
const char* zWIFI_SSID = WIFI_SSID3;
const char* zWIFI_PASSWORD = WIFI_PASSWORD3;

// Wifi settings
#define HOSTNAME "camera"
#define WIFI_CONNECTION_TIMEOUT 5000

// Camera pinout
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void startCameraServer();

void setup() {
  Serial.begin(19200);

  delay(3000);
  Serial.println("\nC'est parti ! 1915 \n");

  Serial.setDebugOutput(true);
  Serial.println();

  camera_init();
  wifi_setup();
  startCameraServer();
  ota_setup();

  // Start OTA server
  otaWebServer();
}

void loop() {
  wifi_connection_manager();
  ArduinoOTA.handle();
  // OTA loop
  serverOTA.handleClient();
}
