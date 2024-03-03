#ifndef WEATHER_H
#define WEATHER_H
#include <Arduino.h>
#include <Arduino_JSON.h>
#include <HTTPClient.h>
#include <Secrets.h>

// Weather class to keep track of current conditions
class Weather {
public:
    // Constructor
    Weather();

    // Destructor
    ~Weather();

    // Method to fetch weather data
    void update();

    // Methods to get specific weather information
    int getTemp() const;
    int getTempMax() const;
    int getTempMin() const;
    int getHumidity() const;
    int getWindSpeed() const;
    int getCloudCover() const;
    String getPrecipType() const;
    String getSunrise() const;
    String getSunset() const;
    String getConditions() const;

    


private:
    // Private member variables to store weather data
    int temp;
    int tempMax;
    int tempMin;
    int humidity;
    int windSpeed;
    int cloudCover;
    String precipType;
    String sunrise;
    String sunset;
    String conditions;
    String API = WEATHER_API;

};

#endif
