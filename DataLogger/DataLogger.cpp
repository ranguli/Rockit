#include <Arduino.h>
#include <SD.h>

#include "DataLogger.h"
#include "Error.h"

DataLogger::DataLogger() {

}

void DataLogger::begin() {
  this->checkSDCardConnected();
}

void DataLogger::checkSDCardConnected() {
  // Checks if the card is present and can be initialized
  if (!SD.begin(17)) {
      fatal_error();
  }
}

String DataLogger::getNewLogFilename() {
  // The filenames for log files are stored in the format "XX.CSV", where "XX" is a two-digit number. 
  // The first log file will be called "00.CSV", the next, "01.CSV", and so on, until "99.CSV" is reached. 
  char filename[] = "00.CSV";
  
  for (uint8_t i = 0; i < 100; i++) {
    filename[0] = i/10 + '0';
    filename[1] = i%10 + '0';

    if (SD.exists(filename)) {
      continue;
    }
    else if (SD.exists(F("99.CSV"))){
      // Once 99 log files have been created, Rockit will refuse to do anymore logging.
      fatal_error();
    }
    break;
  }

  return filename;
}

File DataLogger::open(String filename) {   
    File logFile = SD.open(filename, O_CREAT | O_WRITE); // Only open a new file if it doesn't exist

    if (!logFile) {
      fatal_error();
    }

    this->writeLogFileHeader(logFile);
    return logFile;
}


void DataLogger::writeLogFileHeader(File logFile) {
  logFile.println(F("Time (ms), Altitude (m), Filtered altitude (m), Acceleration (g), Perpendicular acceleration (g), Temperature (C)")); //File header
  logFile.flush(); //Writes data to the SD card
}
