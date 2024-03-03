#ifndef SCREEN_H
#define SCREEN_H
#include <Arduino.h>
#include <ClockTime.h>
#include <Weather.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>



// Screen class to control different views
class Screen {
public:
    // Constructor
    Screen();

    // Destructor
    ~Screen();


    // Digital Clock View
    void digitalClockView(ClockTime rtc, MatrixPanel_I2S_DMA *dma_display, int oldMinute, int oldDay);

    // Date View
    void dateView(ClockTime rtc,  MatrixPanel_I2S_DMA *dma_display, int oldMinute, int oldDay);

    void dateWeatherView(ClockTime rtc,  MatrixPanel_I2S_DMA *dma_display);

private:    
    //Months in a year
    const char* months[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JULY", "AUG", "SEPT", "OCT", "NOV", "DEC"};

};

#endif
