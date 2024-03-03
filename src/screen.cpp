#include <Screen.h>

// Screen class constructor
Screen::Screen() {
    
}

// Destructor
Screen::~Screen() {

}


void Screen::digitalClockView(ClockTime rtc,  MatrixPanel_I2S_DMA *dma_display, int oldMinute, int oldDay) {
    int curHour = 0;

    if(oldMinute != rtc.getMinute()){

        if(rtc.getHour() == 0) {
            curHour = 12;
        } else {
            curHour = rtc.getHour();
        }


        dma_display->fillRect(0, 0, 64, 32, dma_display->color444(0, 0, 0));
        dma_display->setTextSize(2);
        dma_display->setCursor(9, 8);
        if(curHour > 9) {
            dma_display->setCursor(4, 8);
        }

        dma_display->setTextColor(dma_display->color444(15,15,15));
        dma_display->print(curHour);
        dma_display->print(':');
        if (rtc.getMinute() < 10) {
            dma_display->print(0);
        }
        dma_display->print(rtc.getMinute());
        if (rtc.getMilHour() > 11) {
            dma_display->drawPixel(2, 15, dma_display->color444(0,15,15));
            dma_display->drawPixel(2, 14, dma_display->color444(0,15,15));
            dma_display->drawPixel(3, 15, dma_display->color444(0,15,15));
            dma_display->drawPixel(3, 14, dma_display->color444(0,15,15));
        }
    }
}



void Screen::dateView(ClockTime rtc,  MatrixPanel_I2S_DMA *dma_display, int oldMinute, int oldDay) {
    short xOffSet = 2;
    short yOffSet = 2;
    short curHour = 0;
    String curMonth = months[rtc.getMonth()];

    

    if(oldDay != rtc.getDay()){

        Serial.println("Updating Date Display");

        dma_display->fillRect(xOffSet, yOffSet, 25, 9, dma_display->color444(10, 0, 0));
        dma_display->fillRect(xOffSet, yOffSet+9, 25, dma_display->height()-12-yOffSet, dma_display->color444(15, 15, 15));
        dma_display->setTextSize(1);

        if (curMonth.length() == 4) {
            dma_display->setCursor(xOffSet+1, yOffSet+1);
        } else {
            dma_display->setCursor(xOffSet+4, yOffSet+1);
        }
        dma_display->setTextColor(dma_display->color444(15,15,15));
        dma_display->print(curMonth);

        short dateOffSet;
        if(rtc.getDay() < 10) {
            dateOffSet = xOffSet+8;
        } else if (rtc.getDay() < 20){
            dateOffSet = xOffSet+1;
        } else if (rtc.getDay() > 19 && rtc.getDay() != 31 && rtc.getDay() != 21) {
            dateOffSet = xOffSet+2; 
        } else {
            dateOffSet = xOffSet+3;
        }
        dma_display->setCursor(dateOffSet, yOffSet+11);
        dma_display->setTextSize(2); 
        dma_display->setTextColor(dma_display->color444(0,0,0));
        dma_display->print(rtc.getDay());
    }


    if(oldMinute != rtc.getMinute()){

        Serial.println("Updating Time Display");
        if(rtc.getHour() == 0) {
            curHour = 12;
        } else {
            curHour = rtc.getHour();
        }

        dma_display->fillRect(30, 0, 32, 12, dma_display->color444(0, 0, 0));
        dma_display->setTextSize(1); 
        dma_display->setCursor(32, 3);
        dma_display->setTextColor(dma_display->color444(15,15,15));
        dma_display->print(curHour);
        dma_display->print(':');
        if (rtc.getMinute() < 10) {
            dma_display->print(0);
        }
        dma_display->print(rtc.getMinute());
        if (rtc.getMilHour() > 11) {
            dma_display->drawPixel(30, 6, dma_display->color444(0,15,15));
        }
    }

}

void Screen::dateWeatherView(ClockTime rtc,  MatrixPanel_I2S_DMA *dma_display) {
    Weather curWeather;
    curWeather.update();

    dma_display->fillRect(30, 13, 34, 19, dma_display->color444(0, 0, 0));
    dma_display->setTextSize(1); 
    dma_display->setCursor(32, 14);
    dma_display->print("   ");
    dma_display->setTextColor(dma_display->color444(15,2,0));
    dma_display->print(curWeather.getTempMax());
    dma_display->setCursor(32, 22);
    dma_display->print("   ");
    dma_display->setTextColor(dma_display->color444(0,15,15));
    dma_display->print(curWeather.getTempMin());
    dma_display->setCursor(32, 14);
    dma_display->setTextColor(dma_display->color444(15,15,15));
    dma_display->print(curWeather.getTemp());
    dma_display->print(" ");

    Serial.println("Updated Weather");

}