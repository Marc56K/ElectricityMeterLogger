#include "sdcard.h"

bool SdCard::appendLine(const char* fname, const char* msg)
{
    if (init())
    {
        File f = SD.open(fname, FILE_WRITE);
        if (f)
        {
            // f.print(String(t.unixtime()).c_str());
            // f.print("\t");
            // f.println(value);
            f.println(msg);
            f.flush();
            f.close();
        }
        else
        {
            f.println("error opening log.csv");
        }
        release();
        return true;
    }
    return false;
}

void SdCard::release()
{
    SD.end();
}

bool SdCard::init()
{
    pinMode(SS, OUTPUT);
    digitalWrite(SS, HIGH);

    if (!SD.begin(SS))
    {
        Serial.println("Card failed, or not present");
        return false;
    }

    return true;
}