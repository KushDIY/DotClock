#ifndef CLOCKTIME_H
#define CLOCKTIME_H
#include <Arduino.h>
#include <Arduino_JSON.h>
#include <HTTPClient.h>
#include <ESP32Time.h>


// Weather class to keep track of current conditions
class ClockTime {
public:
    // Constructor
    ClockTime();

    // Destructor
    ~ClockTime();

    // Method to fetch weather data
    void resync();

    // Methods to get specific weather information
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMilHour();
    int getMinute();
    int getSecond();

    //Weather api location
    const char* TIME_API = "http://worldtimeapi.org/api/timezone/America/New_York";


private:
    // Private member variables to store weather data
    int syncYear;
    int syncMonth;
    int syncDay;
    int syncHour;
    int syncMinute;
    int syncSecond;
    ESP32Time rtc;

};

#endif
