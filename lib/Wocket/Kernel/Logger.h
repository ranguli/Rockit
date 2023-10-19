#pragma once
#include <Arduino.h>
#include <SD.h>

class DataLogger {
private:
    void checkSDCardConnected();
    void writeLogFileHeader(File logFile);
public:
    DataLogger();
    void begin();
    String getNewLogFilename();
    File open(String filename);
};