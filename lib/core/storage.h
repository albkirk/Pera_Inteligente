/*
## Store any struct in flash ##
 Kudos for this author: Robert Duality4Y [GitHub]
 https://github.com/esp8266/Arduino/issues/1539
*/
#include <EEPROM.h>
#define EEPROMZize 2048

//
//  Create data Struct that will be store on RTC memmory
//
struct {
  unsigned long lastUTCTime = 0;
  unsigned int LastWiFiChannel = 1;
} rtcData;


//
//  AUXILIAR functions to handle EEPROM
//
void EEPROMWritelong(int address, long value) {
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

long EEPROMReadlong(long address) {
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);

  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void loadStruct(void *data_dest, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        char data = EEPROM.read(i + 15);
        ((char *)data_dest)[i] = data;
    }
}

void storeStruct(void *data_source, size_t size)
{
  for(size_t i = 0; i < size; i++)
  {
    char data = ((char *)data_source)[i];
    EEPROM.write(i + 15, data);
  }
  EEPROM.commit();
}


void storage_print() {

  Serial.println("Printing Config");
  Serial.printf("Device Name: %s and Location: %s\n", config.DeviceName, config.Location);
  Serial.printf("ON time[sec]: %d  SLEEP Time[min]: %d  DEEPSLEEP enabled: %d\n", config.ONTime, config.SLEEPTime, config.DEEPSLEEP);
  Serial.printf("LED enabled: %d - TELNET enabled: %d - OTA enabled: %d - WEB enabled: %d\n", config.LED, config.TELNET, config.OTA, config.WEB);
  Serial.printf("WiFi STA Mode: %d\n", config.STAMode);
  Serial.printf("WiFi SSID: %s\n", config.ssid);
  Serial.printf("WiFi Key: %s\n", config.WiFiKey);

  Serial.printf("DHCP enabled: %d\n", config.dhcp);
  if(!config.dhcp) {
      Serial.printf("IP: %d.%d.%d.%d\n", config.IP[0],config.IP[1],config.IP[2],config.IP[3]);
      Serial.printf("Mask: %d.%d.%d.%d\n", config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3]);
      Serial.printf("Gateway: %d.%d.%d.%d\n", config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3]);
  }
  Serial.printf("NTP Server Name: %s\n", config.NTPServerName);
  Serial.printf("NTP update every %ld minutes.\n", config.Update_Time_Via_NTP_Every);
  Serial.printf("Timezone: %ld  -  DayLight: %d\n", config.TimeZone, config.isDayLightSaving);
}


boolean storage_read() {
  Serial.println("Reading Configuration");
    if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' && EEPROMReadlong(3) > 2) {
        Serial.println("Configurarion Found!");
        loadStruct(&config, EEPROMReadlong(3));
      return true;
    }
    else {
    Serial.println("Configurarion NOT FOUND!!!!");
        //Serial.println("Value of 0,1,2: " + String(EEPROM.read(0)) + String(EEPROM.read(1)) + String(EEPROM.read(2)));
        //Serial.println("Value of 3: " + String(EEPROMReadlong(3)));
    return false;
  }
}


void storage_write() {
  Serial.println("Writing Config");
  EEPROM.write(0, 'C');
  EEPROM.write(1, 'F');
  EEPROM.write(2, 'G');
  EEPROMWritelong(3, sizeof(config));
  //Serial.println("Value of 3 WRITE: " + String(sizeof(config)));

  storeStruct(&config, sizeof(config));
  //Serial.println("Value of 0,1,2 READ: " + String(EEPROM.read(0)) + String(EEPROM.read(1)) + String(EEPROM.read(2)));
  //Serial.println("Value of 3 READ: " + String(EEPROMReadlong(3)));
}


void storage_reset() {
  Serial.println("Reseting Config");
  EEPROM.write(0, 'R');
  EEPROM.write(1, 'S');
  EEPROM.write(2, 'T');
  for (size_t i = 3; i < (EEPROMZize-1); i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

boolean RTC_read() {
  if (ESP.rtcUserMemoryRead(0, (uint32_t*) &rtcData, sizeof(rtcData))) return true;
  else return false;
}

boolean RTC_write() {
  if (ESP.rtcUserMemoryWrite(0, (uint32_t*) &rtcData, sizeof(rtcData))) return true;
  else return false;
}

void storage_setup() {
    bool CFG_saved = false;
    RTC_read();                   // Read the RTC memmory
    EEPROM.begin(EEPROMZize);     // define an EEPROM space of 2048 Bytes to store data
    //storage_reset();            // Hack to reset storage during boot
    config_defaults();
    CFG_saved = storage_read();   //When a configuration exists, it uses stored values
    if (!CFG_saved) {             // If NOT, it Set DEFAULT VALUES to "config" struct
        config_defaults();
        storage_write();
    }
    storage_print();
}
