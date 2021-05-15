#include "rtc.h"

#define RTC_GND_PIN 9

void RTC::adjust(const DateTime& t)
{
    pinMode(RTC_GND_PIN, OUTPUT);
    digitalWrite(RTC_GND_PIN, LOW);
    delay(1);
    _rtc.adjust(t);
    pinMode(RTC_GND_PIN, INPUT);
    DateTime _now = now();
    Serial.println(toIsoString(_now));
}

DateTime RTC::now()
{
    pinMode(RTC_GND_PIN, OUTPUT);
    digitalWrite(RTC_GND_PIN, LOW);
    delay(1);

    if (!_rtc.begin())
    {
        Serial.println("Couldn't find RTC");
    }

    DateTime now = _rtc.now();
    pinMode(RTC_GND_PIN, INPUT);

    return now;
}

String RTC::toIsoString(DateTime& t)
{
    char buff[] = "YYYY-MM-DDThh:mm:ss";
    return String(t.toString(buff));
}