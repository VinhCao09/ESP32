#include <TinyGPS++.h>
#include <HardwareSerial.h>



HardwareSerial GPSSerial(1);
TinyGPSPlus gps;

// SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  // ss.begin(GPSBaud);
 GPSSerial.begin(9600, SERIAL_8N1, 16, 17);
 
}

void loop()
{
  while (GPSSerial.available() > 0)
    if (gps.encode(GPSSerial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  
  Serial.println();
}