#pragma once
#include "Arduino.h"

class SerialCli
{
public:
    static bool read(String &cmd, String &arg)
    {
        String buff = "";
        while (Serial.available())
        {
            char c = Serial.read();
            if (c == '\r' || c == '\n')
            {
                continue;
            }

            buff += c;
            if (!Serial.available())
            {
                delay(10);
            }
        }

        buff.trim();

        if (buff.length() == 0)
        {
            cmd = "";
            arg = "";
            return false;
        }

        int idx = buff.indexOf(" ");
        if (idx > -1)
        {
            cmd = buff.substring(0, idx);
            arg = buff.substring(idx + 1);
        }
        else
        {
            cmd = buff;
            arg = "";
        }

        return true;
    }
};