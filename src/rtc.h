#pragma once
#include <Arduino.h>
#include "RTClib.h"

class RTC
{
public:
    void adjust(const DateTime& t);
    DateTime now();
    static String toIsoString(DateTime& t);

private:
    RTC_DS1307 _rtc;
};