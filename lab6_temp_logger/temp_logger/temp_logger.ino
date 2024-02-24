// ===================================================
// RobotDyn SD/RTC Arduino shield example
// Nolan Chandler
// Last revised: 2020-11-18
//
// Meant to serve as a starting point for data logging
// using both a real-time clock (RTC) and a microSD
// card.
//
// Collects data at a given rate, and saves them with
// a timestamp on the SD card to files called
// "LOG000.TXT", "LOG001.TXT", etc. A new file is
// opened every N samples to collect another N samples.
// ===================================================

#include <SPI.h>
#include <SD.h>
// by Adafruit. Must be manually installed
#include "RTClib.h"
const int SD_PIN = 10;
File logfile;
RTC_DS1307 rtc;
float data;
int i = 0;
int N = 10; // Number of samples per file
int waittime_ms = 500; // milliseconds between samples

// ====================================================
// THERMISTOR SETUP STUFF:

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup()
{
// Open serial communications
Serial.begin(9600);
init_RTC();
// (note 24-hour time: 3pm -> 15)
// This line sets the RTC with an
// explicit date & time, for example:
// to set January 21, 2014 at 3:18pm
// you would use the following line:
rtc.adjust(DateTime(2024, 2, 15, 15, 53, 0));
init_SD();
logfile = open_next_logfile();
}
// ==================================================
void loop() {
  if (i < N){
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(T);
  Serial.println(" F"); 

  // save to logifle
  logfile.print("Temperature: ");
  logfile.print(T);
  logfile.println(" F");

  delay(500);

  i++;
  }
  else {
    logfile.close();
    i = 0;
    logfile = open_next_logfile();
  }
}
// =========================================
// initializes the RTC,
// and checks to see if it has been set
// =========================================
void init_RTC()
{
Serial.print("Initializing RTC...");
if (!rtc.begin()) {
Serial.println(" failed!");
while (1);
}
Serial.println(" done!");
if (!rtc.isrunning())
Serial.println(
"WARNING: RTC has not been previously set");
}
// ======================================================
// attempts to initialize the SD card for reading/writing
// ======================================================
void init_SD()
{
Serial.print("Initializing SD card...");
if (!SD.begin(SD_PIN)) {
Serial.println(" failed!");
while (1);
}
Serial.println(" done!");
}
// =======================================================
// Opens the next available log file in SD:/LOGS/
// Write to the file using logfile.print() or println(),
// just like Serial
// =======================================================
File open_next_logfile()
{
char filename[24];
// Create folder for logs if it doesn"t already exist
if (!SD.exists("/LOGS/"))
SD.mkdir("/LOGS/");
// find the first file LOGxxx.TXT that doesn"t exist,
// then create, open and use that file
for (int logn = 0; logn < 1000; logn++) {
sprintf(filename, "/LOGS/LOG%03d.TXT", logn);
if (!SD.exists(filename)) {
Serial.print("Opened \"SD:");
Serial.print(filename);
Serial.println("\" for logging.");
break;
}
}
return SD.open(filename, FILE_WRITE);
}