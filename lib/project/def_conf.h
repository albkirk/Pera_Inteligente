// -- PLATFORM Selection --
//DO NOT UNCOMMENT don't use this! #define ESP32          // already defined elsewhere...
//DO NOT UNCOMMENT don't use this! #define ESP8266        // already defined somewhere...
//#define ESP8285                                         // ESP8285 chip requires reduced MEM space (ex.: remove WEB page)  
#undef ESP8266                                          // To make sure it is not used somewhere... 
//#undef ESP32                                            // To make sure it is not used somewhere... 
#define ESP32C3                                           // ESP32-C3 chip has no ULP.

// -- HARWARE & SOFTWARE Version --
#define BRANDName           "AlBros_Team"                 // Hardware brand name
#define MODELName           "PeraSmart"                   // Hardware model name
#define SWVer               "09.04"                       // Major.Minor Software version (use String 01.00 - 99.99 format !)

// -- Model Variants Definition --                        // Identify variants for acomodade small code changes 
//-> Comment the definitions using //->
//#define ModelVariant                                        // Ex.: MoesHouse cover, Ambisense version,... 
#ifdef ModelVariant
#else
#endif

// -- DIGITAL GPIO to Function Assignment --
#define LED_ESP              8                            // 8266=2, ESP32=22, ESP32C3=8, T-Call=13, TTGoTS=22, T5=19, -1 means NOT used!
#define IR_PIN              -1                            // IR-LED Receiver PIN  -1 means NOT used!
#define BUZZER              -1                            // (Active) Buzzer pin. Suggest to use pin 0. -1 means NOT used!
#define Ext1WakeUP           2                            // External Wake Up pin. (connected to GND, with Parallel Cap).  -1 means NOT used!
#define Reset_Btn           -1                            // Reset button to return to default configuration. -1 means NOT used! 
#define BUT_A                9                            // Button A INPUT pin (used in buttons.h) TTGoTS=35, T5=39, TTGo T7=0
#define BUT_B               -1                            // Button B INPUT pin (used in buttons.h) TTGoTS=34,
#define BUT_C               -1                            // Button C INPUT pin (used in buttons.h) TTGoTS=39,
#define T_Left              -1                            // Touch button Left  pin. TTGoTS=T7, T5=-1, -1 means NOT used!
#define T_Right             -1                            // Touch button Right pin. -1 means NOT used! 

//TouchPins[] = { T0, T1, T2, T3, T4, T5, T6, T7, T8, T9 };  // ALL TOUCH values available!
//TouchPins[] = { 04, 00, 02, 15, 13, 12, 14, 27, 33, 32 };  // ALL TOUCH PIN available!

// -- LED Lights GPIO & Configuration
//#define LED_RGB                                         // Uncoment to be used by color.h library
//#define LED_NEO                                         // Uncoment to be used by color.h library
#define PIN_RED             -1                            // PWM Output PIN for RED  -1 means NOT used!
#define PIN_GREEN           -1                            // PWM Output PIN for GRREN  -1 means NOT used!
#define PIN_BLUE            -1                            // PWM Output PIN for BLUE  -1 means NOT used!
#define NEOPixelsPIN        -1                            // NeoPixels DATA GPIO pin.
#define NEOPixelsNUM        -1                            // Number of NeoPixels LEDs attached

// -- Power Source & Battery Level --
bool BattPowered =       true;                            // Is the device battery powered?
#define Res_Div           true                            // Do you have a Resistor divider (ence needs to multiply by 2)?
#define Res_High           100                            // High Resistor value (in KOhms)
#define Res_Lower          100                            // Lower Resistor value (in KOhms)
#define Batt_L_Thrs         15                            // Battery level threshold [0%-100%] (before slepping forever).
#define Using_ADC         true                            // ESP8266 only. Will you use the external ADC? (if not, it will measure the internal voltage)
//#define IP5306                                          // Power Management chip. TTGo T-Call module uses this.

// -- ADC GPIO & ULP (ESP32 Only)
//#define ULP_Support                                       //ESP32 ULP support. ESP32-S3 and ESP32-C3 not supported.
#ifndef ESP8266
    #define Batt_ADC_PIN     1                            // IO pin for Battery ADC measurement. Default->36,  TFT->36, EPaper->35
    #define NTC_ADC_PIN     -1                            // IO pin for NTC ADC measurement. Default->36,  TFT->36, EPaper->35
    #define LUX_ADC_PIN     -1                            // IO pin for LUX ADC measurement. Default->36,  TFT->36, EPaper->35
#else
    #define Batt_ADC_PIN    A0
    #define NTC_ADC_PIN     A0
    #define LUX_ADC_PIN     A0    
#endif

// -- SPI PIN Definition --
#define MISO_PIN            -1                            // SPI MISO pin, , -1 means NOT used!
#define MOSI_PIN            -1                            // SPI MOSI pin, , -1 means NOT used!
#define CLK_PIN             -1                            // SPI CLK pin,  , -1 means NOT used!
#define CS_PIN              -1                            // SPI CS pin,   , -1 means NOT used!

// -- I2C PIN Definition --
#define SDA_PIN             -1                            // 8266=4, ESP32=21, -1 means NO SDA used!
#define SCK_PIN             -1                            // 8266=5, ESP32=22, -1 means NO SCK used!

// -- I2S PIN Definition --
#define I2S_WS              -1                            // Microphone WS PIN 2
#define I2S_SCK             -1                            // Microphone SCK PIN 14
#define I2S_SD              -1                            // Microphone SD PIN 15

// -- DHT Definition --
#define DHTTYPE              2                            // use 1 for "DHT11", 2 for "DHT22", or 3 for "AM2320" to select the DHT Model
#define DHTPIN              -1                            // GPIO connected to DHT Data PIN. -1 means NO DHT used!

// -- COMUNICATION Definition --
//Bluetooth Definition
#define BLUETOOTH_NAME      MODELName                     // Name of the Bluetooth device
#define BLUETOOTH_Disabled                                // Comment it if using BT. It disables Bluetooth radio to save energy. 

// Module selection
//#define TINY_GSM_MODEM_SIM7020                          // SIMCOM 7020 module. 
//#define TINY_GSM_MODEM_SIM800                           // SIMCOM 800 module. TTGo T-Call module uses this chip
// Modem PINs
#define MODEM_PWKEY         -1                            // T-Call=4, SIM7020E=14, -1 means NOT used!
#define MODEM_RST           -1                            // T-Call=5, -1 means NOT used!
#define MODEM_POWER_ON      -1                            // T-Call=23, -1 means NOT used!
#define MODEM_RX            -1                            // T-Call=26, SIM7020E=4, -1 means NOT used!
#define MODEM_TX            -1                            // T-Call=27, SIM7020E=5, -1 means NOT used!

//GPS PINs
#define GPS_RX              -1                            // T-Call=32, ESP8266=14, -1 means NOT used!
#define GPS_TX              -1                            // T-Call=33, ESP8266=12, -1 means NOT used!
#define GPS_SW              -1                            // Pin for the MOFFET based GPS power switch. -1 means NOT used!

// -- DISPLAY Definition --
#define TFT                                               // Define display type: TFT, EPAPER 
#define ST7789                                            // Define display Model: ST7735 (TTGo TS), ST7789 (T-Display 1.5), GDEH0213B73 (TTGo T5 v2.3)
#define Display_Rotate       3                            // TS=1, EPAPER=3, T-Display=3
#define Display_Width      135                            // X: TS=128, Epaper=212, T-Display=135
#define Display_Height     240                            // Y: TS=128, Epaper=104, T-Display=240
#define Display_BACKLIGHT   -1                            // Display Backlight, TS->-1, T5->-1, -1 means NOT used!
#define Display_CS          -1                            // Display CS pin,    TS->16, T5-> 5  -1 means NOT used!
#define Display_DC          -1                            // Display DC pin,    TS->17, T5->17, -1 means NOT used!
#define Display_MOSI        -1                            // Display MOSI pin,  TS->23, T5->23, -1 means NOT used!
#define Display_CLK         -1                            // Display CLK pin,   TS-> 5, T5->18, -1 means NOT used!
#define Display_RST         -1                            // Display RST pin,   TS-> 9, T5->16, -1 means NOT used!
#define Display_BUSY        -1                            // Display BUSY pin,  TS->-1, T5-> 4  -1 means NOT used!


void config_defaults() {
    Serial.println("Setting config Default values");

    strcpy(config.DeviceName, MODELName);                 // Device Name
    strcpy(config.Location, "Home");                      // Device Location
    strcpy(config.ClientID, "001001");                    // Client ID (used on MQTT)
    config.ONTime = 0;                                    // 0-255 seconds (Byte range)
    config.SLEEPTime = 0;                                 // 0-255 minutes (Byte range)
    config.DEEPSLEEP = true;                              // 0 - Disabled, 1 - Enabled
    config.LED = true;                                    // 0 - OFF, 1 - ON
    config.TELNET = false;                                // 0 - Disabled, 1 - Enabled
    config.OTA = false;                                   // 0 - Disabled, 1 - Enabled
    config.WEB = false;                                   // 0 - Disabled, 1 - Enabled
    config.Remote_Allow = true;                           // 0 - Not Allow, 1 - Allow remote operation
    config.STAMode = true;                                // 0 - AP or AP+STA Mode, 1 - Station only Mode
    config.APMode = false;                                // 0 - AP Mode Disabled, 1 - AP Mode Enabled
    strcpy(config.SSID, "WiFiCasaN");                     // Wireless LAN SSID (STA mode)
    strcpy(config.WiFiKey, "12345678");                   // Wireless LAN Key (STA mode)
    config.DHCP = true;                                   // 0 - Static IP, 1 - DHCP
    config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 1; config.IP[3] = 10;
    config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;
    config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 1;
    config.DNS_IP[0] = 192; config.DNS_IP[1] = 168; config.DNS_IP[2] = 1; config.DNS_IP[3] = 93;
    strcpy(config.NTPServerName, "pt.pool.ntp.org");      // NTP Server
    config.Update_Time_Via_NTP_Every = 1200;              // Time in minutes to re-sync the clock
    config.TimeZone = 0;                                  // -12 to 13. See Page_NTPSettings.h why using -120 to 130 on the code.
    config.isDayLightSaving = 1;                          // 0 - Disabled, 1 - Enabled
    strcpy(config.MQTT_Server, "iothubna.hopto.org");     // MQTT Broker Server (URL or IP)
    config.MQTT_Port = 1883;                              // MQTT Broker TCP port
    config.MQTT_Secure = false;                           // 0 - Unsecure, 1 - TLS v1.2 Secured!!
    strcpy(config.MQTT_User, "mqtt");                     // MQTT Broker username
    strcpy(config.MQTT_Password, "mqttpass!");            // MQTT Broker password
    strcpy(config.UPDATE_Server, "iothubna.hopto.org");   // UPDATE Server (URL or IP)
    config.UPDATE_Port = 8123;                            // UPDATE Server TCP port
    strcpy(config.UPDATE_User, "user");                   // UPDATE Server username
    strcpy(config.UPDATE_Password, "1q2w3e4r");           // UPDATE Server password
    strcpy(config.SIMCardPIN, "1234");                    // SIM card PIN
    strcpy(config.APN, "internet.vodafone.pt");           // Modem (GPRS/NB-IoT) APN name 
    strcpy(config.MODEM_User, "none");                    // APN username
    strcpy(config.MODEM_Password, "none");                // APN password
    strcpy(config.WEB_User, "admin");                     // WEB Server username
    strcpy(config.WEB_Password, "admin");                 // WEB Server password
    config.Temp_Corr = 0.0;                               // Sensor Temperature Correction Factor, typically due to electronic self heat.
    config.LDO_Corr = 0.00;                               // Battery Voltage [volt] corrective Factor due to LDO/Diode voltage drop
    config.HW_Module = false;                             // Is HW module plugged (ex.: GPS hardware)used / connected?
    config.HASSIO_CFG = false;                            // Is HASSIO configured? If not, it should perform the discovery.
    config.DEBUG = true;                                  // 0 - No serial msgs, 1 - Debug msg sent to serial interface
    config.SW_Upgraded = false;                           // Is SW Upgrade completed? If not, clean the house and Update status.
    config.SWITCH_Default = false;                        // 0 - OFF, 1 - ON - Default SWITCH Status 
    config.UPPER_LEVEL = 70;                              // level where blinds should stay when pressing double UP
    config.LOWER_LEVEL = 10;                              // level where blinds should stay when pressing double DN
    config.MIN_TRAVEL = 0;                                // Time reference for fully DN position
    config.MAX_TRAVEL = 17000;                            // Time required to go from fully DN to fully UP
    config.Voltage_Multiplier = 256000;                   // Unit: us/V
    config.Current_Multiplier =  23000;                   // Unit: us/A
    config.Power_Multiplier   = 678000;                   // Unit: us/W
    strcpy(config.InitColor, "#EEEEEE");                  // RGB Initial color (when powering ON)
    config.Volume = 100;                                  // Speaker volume [0-100%].
    config.Alarm_State = false;                           // Alarm state (true -> Ring / False -> Not Ring)
    config.AlarmDateTime = {0, 1, 0, 0, 0, 0, 7, true, 0};// Alarm DateTime structure
}
