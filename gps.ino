#include <SoftwareSerial.h>

#include <TinyGPS.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 3(rx) and 4(tx).
*/

TinyGPS gps;
SoftwareSerial ss(3,2);

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);

  Serial.println();
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
       //6Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;

    
    
    float falt = gps.f_altitude();
    unsigned long age;
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long fix_age;
 
    gps.crack_datetime(&year, &month, &day,&hour, &minute, &second, &hundredths, &fix_age);
    Serial.print(month);
    Serial.print(",");
    Serial.print(day);
    Serial.print(",");
    Serial.println(year);
    
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(second);
    gps.f_get_position(&flat, &flon, &age);
    
//  Serial.print("LAT=");
//    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
//  Serial.print(" LON=");
 //   Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//   Serial.print(" SAT=");
//   Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
//   Serial.print(" Altitude=");
    Serial.println(flat,6);
    Serial.println(flon,6);
    Serial.println(falt);
    
    
  }
 else{
  Serial.println("no fix");
   }
}

