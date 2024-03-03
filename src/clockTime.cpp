#include <ClockTime.h>

// ClockTime class constructor
ClockTime::ClockTime() {
    // Initialize member variables
    syncYear = 0;
    syncMonth = 0;
    syncDay = 0;
    syncHour = 0;
    syncMinute = 0;
    syncSecond = 0;
}

// Destructor
ClockTime::~ClockTime() {

}

// Method to resync ClockTime data
void ClockTime::resync() {
    // Make GET request to WorldTimeAPI with timezone parameter set to EST
    HTTPClient http;
    String payload;
    http.begin(TIME_API);

    Serial.println("Syncing Time");
    if (http.GET() == HTTP_CODE_OK){
        payload = http.getString();
        Serial.println(payload); 

        // Parse the payload to extract the datetime field
        int startIdx = payload.indexOf("datetime\":\"") + 11; // Find the start of datetime string
        int endIdx = payload.indexOf("\"", startIdx); // Find the end of datetime string
        String dateTimeStr = payload.substring(startIdx, endIdx); // Extract the datetime string
        Serial.print("Datetime: ");
        Serial.println(dateTimeStr);

        // Convert datetime string to RTC-compatible format (YYYY-MM-DDTHH:MM:SS)
        syncYear = dateTimeStr.substring(0, 4).toInt();
        syncMonth = dateTimeStr.substring(5, 7).toInt();
        syncDay = dateTimeStr.substring(8, 10).toInt();
        syncHour = dateTimeStr.substring(11, 13).toInt();
        syncMinute = dateTimeStr.substring(14, 16).toInt();
        syncSecond = dateTimeStr.substring(17, 19).toInt();


        rtc.setTime(syncSecond, syncMinute, syncHour, syncDay, syncMonth, syncYear); // Set the time on RTC

        Serial.println("RTC time set successfully");
        Serial.println(rtc.getDateTime());

    } else {
        Serial.print("Error accessing WorldTimeAPI. HTTP error code: ");
        Serial.println(http.GET());
    }

    http.end();

}

// Methods to get specific ClockTime information
int ClockTime::getYear() {
    return rtc.getYear();
}

int ClockTime::getMonth() {
    return rtc.getMonth();
}

int ClockTime::getDay() {
    return rtc.getDay();
}

int ClockTime::getHour() {
    return rtc.getHour();
}

int ClockTime::getMilHour() {
    return rtc.getHour(true);
}

int ClockTime::getMinute() {
    return rtc.getMinute();
}

int ClockTime::getSecond() {
    return rtc.getSecond();
}
