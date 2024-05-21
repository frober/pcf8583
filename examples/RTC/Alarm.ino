#include "PCF8583.h"
PCF8583 rtc(0xA0);
AlarmTime dt;

#define rtc_int 3                           // for RTC Interrupt

byte Sec  = 0;
byte Min  = 0;
byte Hour = 0;

char buf[30];                               // help for change to string


void setup()
{
  Serial.begin(9600);
  pinMode(rtc_int, INPUT_PULLUP);
  rtc.setTime(0, 40, 12);

  getRTCtime();     // test the time from RTC
  setAlarmTime();   // setting the alarm time
  getAlarmTime();   // control the setting alarm time

  attachInterrupt(digitalPinToInterrupt(rtc_int), RTCint, FALLING);
}

void loop()
{ 
  // do anything...
}

void RTCint()
{
  Serial.println("RTC Alarm...");
  rtc.clearInterrupt();   // reset the INT Pin from the RTC Chip
  
  // setup new alarmtime or
  // rtc.enableAlarm();   // for the same alarm time
}

void getRTCtime()
{
  unsigned long Time = rtc.getTime() / 1000;          // Returns milliseconds since midnight (/1000 = sec)
  Serial.print(F("get time from RTC: "));
  Serial.print(Time);
  Serial.println(F(" s since midnight"));
  
  Sec  = rtc.getSecond();
  Min  = rtc.getMinute();
  Hour = rtc.getHour();
  sprintf(buf,"%02d:%02d:%02d",Hour,Min,Sec);
  Serial.print(F("get time from RTC: "));
  Serial.println(buf);
}

void setAlarmTime()
{
  Serial.println("setting alarm time");
  Hour = 12;
  Min  = 45;
  Sec  = 0;
  rtc.disableAlarm();
  rtc.setAlarm(Sec, Min, Hour);
  rtc.enableAlarm();
}

void getAlarmTime()
{
  dt = rtc.getAlarm();
  sprintf(buf,", get Alarm Time (d:h:m:s): %02d:%02d:%02d:%02d",dt.day,dt.hour,dt.minute,dt.second);
  Serial.println(buf);
   
}
