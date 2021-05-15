#include "rtc.h"
#include "sdcard.h"
#include "serial_cli.hpp"
#include "LowPower.h"

RTC rtc;
SdCard sdcard;

volatile bool pin2Interrupt = false;
void pin2ISR()
{
    pin2Interrupt = true;
}

bool pin2InterruptOccurred()
{
    bool result = pin2Interrupt;
    pin2Interrupt = false;
    return result;
}

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(2, INPUT);
    attachInterrupt(digitalPinToInterrupt(2), pin2ISR, FALLING);

    DateTime now = rtc.now();
    Serial.println(String("Current time: ") + RTC::toIsoString(now));

    Serial.println(F("Waiting 10 seconds for user intput:"));
    Serial.println(F(" e.g. setclock 2020-06-25T15:29:37"));

    while (millis() < 10000)
    {
        String cmd, arg;
        if (SerialCli::read(cmd, arg))
        {
            Serial.println(cmd + "->" + arg);
            if (cmd == "setclock")
            {
                rtc.adjust(DateTime(arg.c_str()));
            }
        }
        delay(100);
    }

    Serial.println(F("started"));
}

void loop()
{
    if (pin2InterruptOccurred())
    {
        digitalWrite(LED_BUILTIN, HIGH);
        DateTime now = rtc.now();
        String nowStr = RTC::toIsoString(now);
        Serial.println(nowStr);
        sdcard.appendLine("log.csv", (String(now.unixtime()) + "\t" + nowStr).c_str());
        digitalWrite(LED_BUILTIN, LOW);
    }
    Serial.flush();
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}