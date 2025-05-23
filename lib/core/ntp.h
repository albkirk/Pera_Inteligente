#define LEAP_YEAR(Y) (((1970 + Y) > 0) && !((1970 + Y) % 4) && (((1970 + Y) % 100) || !((1970 + Y) % 400)))

static strDateTime DateTime;              // Global DateTime structure
strDateTime LastDateTime = {25, 61, 61, 1, 13, 32, 8};
static const uint8_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const String WeekDays[] = {"Weekends", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", "Daily", "Work Days"};

volatile unsigned long UTCTimeStamp = 0;  // GLOBAL TIME var ( Will be retrieved via NTP protocol)
volatile unsigned long UnixTimeStamp = 0; // GLOBAL TIME var ( Will be devivated from UTCTimeStamp for local time zone)
unsigned long RefMillis = 0;              // Millis val for reference
bool NTP_Sync = false;                    // Is NTP synched?
unsigned int NTP_Retry = 120;             // Timer to retry the NTP connection
unsigned long NTP_LastTime = 0;           // Last NTP connection attempt time stamp
int NTP_errors = 0;                       // NTP errors Counter
volatile unsigned long cur_utctime;       // Auxiliary var
volatile unsigned long cur_unixtime;      // Auxiliary var
static unsigned long ntpNOW = 0;          // Auxiliary var for millis


String leadzero(byte DTValue) {
  if (DTValue <=9) return ("0" + String(DTValue));
  else return String(DTValue);
}

strDateTime ConvertTimeStamp(unsigned long _tempTimeStamp)
{
  strDateTime _tempDateTime;
  uint8_t year;
  uint8_t month, monthLength;
  uint32_t time;
  unsigned long days;

  time = (uint32_t)_tempTimeStamp;
  _tempDateTime.second = time % 60;
  time /= 60;                                // now it is minutes
  _tempDateTime.minute = time % 60;
  time /= 60;                                // now it is hours
  _tempDateTime.hour = time % 24;
  time /= 24;                                // now it is days
  _tempDateTime.wday = ((time + 4) % 7) + 1; // Sunday is day 1

  year = 0;
  days = 0;
  while ((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time)
  {
    year++;
  }
  _tempDateTime.year = year;                 // year is offset from 1970

  days -= LEAP_YEAR(year) ? 366 : 365;
  time -= days;                              // now it is days in this year, starting at 0

  days = 0;
  month = 0;
  monthLength = 0;
  for (month = 0; month < 12; month++)
  {
    if (month == 1)
    { // february
      if (LEAP_YEAR(year))
      {
        monthLength = 29;
      }
      else
      {
        monthLength = 28;
      }
    }
    else
    {
      monthLength = monthDays[month];
    }

    if (time >= monthLength)
    {
      time -= monthLength;
    }
    else
    {
      break;
    }
  }
  _tempDateTime.month = month + 1;           // jan is month 1
  _tempDateTime.day = time + 1;              // day of month
  _tempDateTime.year += 1970;

  return _tempDateTime;
}

//
// Summertime calculates the daylight saving time for middle Europe. Input: Unixtime in UTC
//
boolean summerTime(unsigned long _timeStamp)
{
  strDateTime _tempDateTime = ConvertTimeStamp(_timeStamp);
  // printTime("Innerhalb ", _tempDateTime);

  if (_tempDateTime.month < 3 || _tempDateTime.month > 10)
    return false; // NOT Summertime in Jan, Feb, Nov, Dez
  if (_tempDateTime.month > 3 && _tempDateTime.month < 10)
    return true; // Summertime in Apr, Mai, Jun, Jul, Aug, Sep
  if (_tempDateTime.month == 3 && ((_tempDateTime.hour + 24 * _tempDateTime.day) >= (3 + 24 * (31 - (5 * _tempDateTime.year / 4 + 4) % 7))))
    return true;
  else if (_tempDateTime.month == 10 && ((_tempDateTime.hour + 24 * _tempDateTime.day) < (3 + 24 * (31 - (5 * _tempDateTime.year / 4 + 1) % 7))))
    return true;
  else
    return false;
}

unsigned long adjustTimeZone(unsigned long _timeStamp, int _timeZone, bool _isDayLightSavingSaving)
{
  // strDateTime _tempDateTime;
  _timeStamp += _timeZone * 10 * 360;        // adjust timezone
  // printTime("Innerhalb adjustTimeZone ", ConvertTimeStamp(_timeStamp));
  if (_isDayLightSavingSaving && summerTime(_timeStamp))
    _timeStamp += 3600;                      // adding summerTime hour
  return _timeStamp;
}

void getNTPtime(unsigned long timeout_sync = 1000UL)
{
  bool loop_timeOut = true;
  NTP_Sync = false;
  unsigned long NTPTime = 0; // Resetting value to 0

  if (WIFI_state != WL_CONNECTED)
    telnet_println("NTP ERROR! ==> NO Internet connection!");
  else
  {
    myconfigTime("TZ_Etc_UTC", config.NTPServerName, config.NTPServerName, config.NTPServerName);
    unsigned long start_sync = millis();
    loop_timeOut = false;
    while (!NTP_Sync && !loop_timeOut)
    {
      NTPTime = time(nullptr);
      RefMillis = millis();                  // Exact moment that NTP data was retrived
      if (millis() - start_sync > timeout_sync)
        loop_timeOut = true;
      if (NTPTime > 31536000UL)
        NTP_Sync = true;
      yield();
    }
    if (NTP_Sync)
    {
      UTCTimeStamp = NTPTime;
      ntpNOW = millis();                     // To make sure that it 1st value is valid
      telnet_println("NTP extracted from Internet with SUCCESS!");
    }
  }
  if (ESPResetReason() == "Deep-Sleep Wake" && loop_timeOut)
  {
    UTCTimeStamp = rtcData.lastUTCTime + config.SLEEPTime * 60 + 1; // + 1 is an empirical number to adjust the time error.
    RefMillis = 0;
    telnet_println("NTP calculated from RTC");
  }
  if (UTCTimeStamp > 31536000UL)
  {
    // const unsigned long seventyYears = 2208988800UL;
    // UTCTimeStamp = secsSince1900 - seventyYears;      // store "Coordinated Universal Time" (UTC) time stamp
    UTCTimeStamp = UTCTimeStamp - RefMillis / 1000; // store UTC time stamp since millis() = 0 ... aka @ Boot time!
    UnixTimeStamp = adjustTimeZone(UTCTimeStamp, config.TimeZone, config.isDayLightSaving);
  }
  else
  {
    NTP_errors++;
    telnet_println("NTP ERROR! ==> NO valid Local Date / Time");
  }
}

unsigned long curUTCTime()
{
  if (ntpNOW < RefMillis)
  { // If true, it would mean the millis() counter had looped.
    UTCTimeStamp = UTCTimeStamp + 4294967295UL;
    NTP_Sync = false;
  }
  ntpNOW = millis();
  cur_utctime = UTCTimeStamp + ntpNOW / 1000;
  // telnet_println("Current UTC time: " + String(cur_utctime));
  return cur_utctime;
}

unsigned long curUnixTime()
{
  if (ntpNOW < RefMillis)
  { // If true, it would mean the millis() counter had looped.
    UTCTimeStamp = UTCTimeStamp + 4294967295UL;
    UnixTimeStamp = adjustTimeZone(UTCTimeStamp, config.TimeZone, config.isDayLightSaving);
    RefMillis = 0;
    NTP_Sync = false;
  }
  ntpNOW = millis();
  cur_unixtime = UnixTimeStamp + ntpNOW / 1000;
  // telnet_println("Current UNIX time: " + String(cur_unixtime));
  return cur_unixtime;
}

String printDateTime(unsigned long _timeStamp) {
  strDateTime _tempDateTime = ConvertTimeStamp(_timeStamp);
  String cdt_var = "";
  cdt_var = String(WeekDays[_tempDateTime.wday]) + ", " + String(_tempDateTime.year) + "/" + leadzero(_tempDateTime.month) + "/" + leadzero(_tempDateTime.day);
  cdt_var += "  " + leadzero(_tempDateTime.hour) + ":" + leadzero(_tempDateTime.minute) + ":" + leadzero(_tempDateTime.second);
  return cdt_var;   
}

String curDateTime()
{
  cur_unixtime = curUnixTime();
  DateTime = ConvertTimeStamp(cur_unixtime);
  return printDateTime(cur_unixtime);
}

void ntp_setup()
{
  getNTPtime();
  if (NTP_Sync)
  {
    telnet_println("Current Local Date / Time: " + curDateTime(), true);
  }
}

void ntp_loop()
{
  if (!NTP_Sync)
  {
    if (millis() - NTP_LastTime > (NTP_Retry * 1000))
    {
      NTP_errors++;
      telnet_println("in loop function NTP NOT sync! #: " + String(NTP_errors));
      NTP_LastTime = millis();
      getNTPtime();
    }
  }
  else
  {
    if (millis() - NTP_LastTime > (config.Update_Time_Via_NTP_Every * 60 * 1000))
    {
      NTP_LastTime = millis();
      getNTPtime();
    }
  }
  yield();
}
