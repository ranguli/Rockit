#include <Arduino.h>
#include <SD.h>

#ifndef ROCKIT_DATALOGGER_H
#define ROCKIT_DATALOGGER_H

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

#endif // ROCKIT_DATALOGGER_H
