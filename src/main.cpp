#include <Arduino.h>
#include <FS.h> // Include the SPIFFS library for file operations
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <HTTPClient.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32Time.h>
#include <ClockTime.h>
#include <Screen.h>
#include <Secrets.h>
// DotClock Project
  
// Declare constants
#define PANEL_RES_X 64      // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32      // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1       // Total number of panels chained one to another

// Default brightness of display
short brightVal = 20;

// Pin locations for buttons
short const brightButtPin = 35;
short const modeButtPin = 34;

// Set and update time using WorldClockAPI
ClockTime rtc = ClockTime();

Screen display = Screen();

// Declare a MatrixPanel instance
MatrixPanel_I2S_DMA *dma_display = nullptr;

// Variables to track when a time value changes
int oldDay = -1;
int oldMinute = -1;
int weatherCheck = -1;
int timeResync = -1;

// Current display mode
short displayMode = 0;

// Determines if it should recheck weather
bool updateWeather = true;

// Initialize the wifi for the ESP32
void initWiFi() {
  // Initialize WiFi Mode
  WiFi.mode(WIFI_STA);
  
  Serial.println();
  Serial.print("Connecting Wifi: ");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Convert String to const char*

  delay(250);
  // Wait for WiFi to connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.println(WiFi.localIP());
  }
  Serial.println();
  // WiFi connected successfully
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
}

// Called at the start of the ESP32 turning on
void setup() {

  // Begin the Serial Monitor
  Serial.begin(115200);
  WiFi.disconnect();
  delay(100);

  // Connect to WiFi
  initWiFi();

  // Set the brightness and mode buttons as inputs
  pinMode(brightButtPin, INPUT);
  pinMode(modeButtPin, INPUT);

  // Module configuration
  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,   // module width
    PANEL_RES_Y,   // module height
    PANEL_CHAIN    // Chain length
  );
  mxconfig.gpio.e = 18;
  mxconfig.clkphase = false;
  mxconfig.driver = HUB75_I2S_CFG::FM6126A;

  // Display Setup
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(brightVal); // 0-255
  dma_display->clearScreen();

  rtc.resync();
}

void loop() {

//  Updates the display based on the mode it is in
  switch (displayMode){
    case 1:
//    Case 0 displays the date view
      if(oldMinute != rtc.getMinute()) {
        display.dateView(rtc, dma_display, oldMinute, oldDay);
        oldMinute = rtc.getMinute();
        if((rtc.getMinute() % 10 == 0 && rtc.getMinute() != timeResync)) {
          rtc.resync();
          timeResync = rtc.getMinute();
        }
      }

      if(oldDay != rtc.getDay()){
        display.dateView(rtc, dma_display, oldMinute, oldDay);
        oldDay = rtc.getDay();
      }
      

//    If the WiFi is connected it will display the current weather
      if (WiFi.status() == WL_CONNECTED) {
        if((rtc.getMinute() % 10 == 0 && rtc.getMinute() != weatherCheck) || updateWeather) {
          updateWeather = false;
          weatherCheck = rtc.getMinute();
          display.dateWeatherView(rtc, dma_display);
        }
      } 
      break;
    case 0:
      //    Case 1 displays the digitalTime view 
      if(oldMinute != rtc.getMinute()) {
        display.digitalClockView(rtc, dma_display, oldMinute, oldDay);
        oldMinute = rtc.getMinute();
        if((rtc.getMinute() % 10 == 0 && rtc.getMinute() != timeResync)) {
          rtc.resync();
          timeResync = rtc.getMinute();
        }
      }
//    Sets updateWeather to true so that it updates when changing modes
      updateWeather = true;
      
      break;

    case 2:
//    Case 2 displays the weatherInfo screen

      break;
  }

//  Checks to see if buttons were pressed
  if (digitalRead(brightButtPin) == HIGH){
    delay(250);
    if (digitalRead(brightButtPin) == HIGH){
      int tempCount = 0;
//    If brightness button is held down for .750 seconds then it goes into time set mode  
      while(digitalRead(brightButtPin) == HIGH) {
        tempCount+=1;
        if(digitalRead(brightButtPin) == HIGH && tempCount >= 750){
//        Serial.println("SETTING TIME");
          dma_display->clearScreen();
          rtc.resync();
          break;
        }
        delay(1);
      }
    } else {
        if(brightVal < 5) {
          if(brightVal == 0) {
            brightVal = 3;
          } else {
            brightVal = 20;
          }
        } else {
          brightVal+=15;
        }
        if(brightVal > 80) {
          brightVal = 0;
      }
      dma_display->setBrightness8(brightVal);
      Serial.print("Set brightness to: ");
      Serial.println(brightVal);
    }
  }
  
  if (digitalRead(modeButtPin) == HIGH){
    displayMode+=1;
    if(displayMode > 1) {
      displayMode = 0;
    }
    oldDay= -1;
    oldMinute = -1;
    delay(250);
    dma_display->clearScreen();
  }

  
}