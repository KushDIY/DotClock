#include "Weather.h"

// Weather class constructor
Weather::Weather() {
    // Initialize member variables
    temp = 0;
    tempMax = 0;
    tempMin = 0;
    humidity = 0;
    windSpeed = 0;
    cloudCover = 0;
    precipType = "Unknown";
    sunrise = "Unknown";
    sunset = "Unknown";
    conditions = "Unknown";

}

// Destructor
Weather::~Weather() {

}

// Method to fetch weather data and update member variables
void Weather::update() {
    // Perform HTTP request to fetch weather data from API
    // Parse the JSON response and update member variables
    Serial.println("Attempting to get weather");
    HTTPClient http;
    String payload;

    http.begin(WEATHER_API);
  
    Serial.println("Getting Payload");
    if (http.GET() == HTTP_CODE_OK){
        payload = http.getString();
        Serial.println(payload);    
    }   
    else {
    Serial.print("Error code: ");

    }
    http.end();

    // Parse the weather data
    JSONVar weatherData = JSON.parse(payload);
    
    if (JSON.typeof(weatherData) == "undefined") {
      Serial.println("Parsing input failed!");
      return;
    }

    // Set the values for weather attributes
    temp = int(round((double)(weatherData["currentConditions"]["temp"])));
    tempMax = int(round((double)(weatherData["days"][0]["tempmax"])));
    tempMin = int(round((double)(weatherData["days"][0]["tempmin"])));
    humidity = int(round((double)(weatherData["currentConditions"]["humidity"])));
    windSpeed = int(round((double)(weatherData["currentConditions"]["windspeed"])));
    cloudCover = int(round((double)(weatherData["currentConditions"]["cloudcover"])));
    precipType = JSON.stringify(weatherData["currentConditions"][0]["preciptype"]);
    sunrise = JSON.stringify(weatherData["days"][0]["sunrise"]);
    sunset = JSON.stringify(weatherData["days"][0]["sunset"]);
    conditions = JSON.stringify(weatherData["currentConditions"]["conditions"]);

}

// Methods to get specific weather information
int Weather::getTemp() const {
    return temp;
}

int Weather::getTempMax() const {
    return tempMax;
}

int Weather::getTempMin() const {
    return tempMin;
}

int Weather::getHumidity() const {
    return humidity;
}

int Weather::getWindSpeed() const {
    return windSpeed;
}

int Weather::getCloudCover() const {
    return cloudCover;
}

String Weather::getPrecipType() const {
    return precipType;
}

String Weather::getSunrise() const {
    return sunrise;
}

String Weather::getSunset() const {
    return sunset;
}
    
String Weather::getConditions() const {
    return conditions;
}

