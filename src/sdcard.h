#pragma once
#include <SPI.h>
#include <SD.h>

class SdCard
{
public:
    bool appendLine(const char* fname, const char* msg);

private:
    bool init();
    void release(); 
};