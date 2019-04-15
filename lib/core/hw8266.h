#include "Adafruit_Sensor.h"
#include <DHT.h>

//System Parameters
#define ChipID HEXtoUpperString(ESP.getChipId(), 6)
#define ESP_SSID String("ESP-" + ChipID)              // SSID used as Acces Point
#define Number_of_measures 10                         // Number of value samples (measurements) to calculate average

// ADC to internal voltage
#if Using_ADC == false
    ADC_MODE(ADC_VCC)                       // Get voltage from Internal ADC
#endif

// Battery & ESP Voltage
#define Batt_Max float(4.2)                 // Battery Highest voltage.  [v]
#define Batt_Min float(3.0)                 // Battery lowest voltage.   [v]
#define Vcc float(3.3)                      // Theoretical/Typical ESP voltage. [v]
#define VADC_MAX float(1.0)                 // Maximum ADC Voltage input
float voltage = 0.0;                        // Input Voltage [v]
float Batt_Level = 100.0;                   // Battery level [0%-100%]

// Temperature Variables and Sensors
#define samp_intv int(300)                  // Temperature and Humidity Sampling Interval value in seconds
unsigned long curr_time;                    // Variable used to write the current time
unsigned long last_sample;                  // Variable used to write time the last sample was taken

// Initialize DHT sensor.
#define DHTTYPE DHT22                       // using the DHT22 Model
DHT dht_val(DHTPIN, DHTTYPE);

//NTC temperature
#define Rs 47000                            // 47KOhm Voltage Dividor Resistor

// Timers for millis used on Sleeping and LED flash
unsigned long ONTime_Offset=0;
unsigned long Extend_time=0;
unsigned long now_millis=0;
unsigned long Pace_millis=3000;
unsigned long LED_millis=300;               // 10 slots available (3000 / 300)
unsigned long BUZZER_millis=500;            // 6 Buzz beeps maximum  (3000 / 500)

// Functions //
String HEXtoUpperString(uint32_t hexval, uint hexlen) {
    String strgval = String(hexval, HEX);
    String PADZero;
    for (uint i = 0; i < (hexlen - strgval.length()) ; i++) PADZero +="0";
    strgval = PADZero + strgval;
    char buffer[hexlen+1];
    strcpy(buffer, strgval.c_str());
    for (uint i = 0; i < strgval.length() ; i++) {
        if (char(buffer[i]) >= 97 ) buffer[i] = (char)(char(buffer[i] - 32));
    }
    return String(buffer);
}

//  ESP8266
void GoingToSleep(byte Time_minutes = 0) {
  //rtcData.lastUTCTime = curUnixTime();
  //RTC_write();
  ESP.deepSleep( Time_minutes * 60 * 1000000);   // time in minutes converted to microseconds
}


float getVoltage() {
    // return battery level in Percentage [0 - 100%]
    voltage = 0;
    for(int i = 0; i < Number_of_measures; i++) {
        if (Using_ADC) {voltage += analogRead(A0) * Vcc;}
        else {voltage += ESP.getVcc();} // only later, the (final) measurement will be divided by 1000
        delay(50);
    };
    voltage = voltage / Number_of_measures;
    voltage = voltage / 1000.0 + LDO_Corr;
    Serial.println("Averaged and Corrected Voltage: " + String(voltage));
    return ((voltage - Batt_Min) / (Batt_Max - Batt_Min)) * 100.0;
}

long getRSSI() {
    // return WiFi RSSI Strength signal [dBm]
    long r = 0;

    for(int i = 0; i < Number_of_measures; i++) {
        r += WiFi.RSSI();
    }
    r = r /Number_of_measures;
    return r;
}


float getNTCThermister() {
  // Return temperature as Celsius
  int val = 0;
  for(int i = 0; i < Number_of_measures; i++) {       // ADC value is read N times
      val += analogRead(A0);
      delay(10);
  }
  val = val / Number_of_measures;

  double V_NTC = (double)val / 1024;
  double R_NTC = (Rs * V_NTC) / (Vcc - V_NTC);
  R_NTC = log(R_NTC);
  double Tmp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * R_NTC * R_NTC ))* R_NTC );
  float Temp = (float)Tmp - 273.15 + config.Temp_Corr;
  return Temp;
}


float getTemperature() {
    // Return temperature as Celsius (DHT22 range -40 to +125 degrees Celsius) or -100 if error
  if (DHTPIN>=0) {
      float t;
      int n = 0;

      while (n < 10) {
          t = dht_val.readTemperature() + config.Temp_Corr;
          // Check if any reads failed and exit.
          if (isnan(t)) {
              Serial.println("Failed to read temperature from DHT sensor!");
              delay(1000);
              //t = NULL;
              n ++;
          }
          else {
              //Serial.print(t);
              return t;
          }
    };
  }
  else {
    return getNTCThermister();
  }
  return -100;
}


float getHumidity() {
    // Read Humidity as Percentage (0-100%) or -1 if error

  float h;
  int n = 0;

  while (n < 10 ) {
    h = dht_val.readHumidity();
    // Check if any reads failed and exit.
    if (isnan(h)) {
      Serial.println("Failed to read humidity from DHT sensor!");
      delay(1000);
      //h = NULL;
      n ++;
    }
    else {
      //Serial.print(h);
      return h;
    }
  }
return -1;
}

void ESPBoot() {
  Serial.println("Booting in 3 seconds...");
  delay(3000);
  ESP.restart();
}

String ESPWakeUpReason() {
  return ESP.getResetReason();
}

void FormatConfig() {                                 // WARNING!! To be used only as last resource!!!
    Serial.println(ESP.eraseConfig());
    delay(5000);
    ESP.reset();
}

void blink_LED(int slot) {                            // slot range 1 to 10 =>> 3000/300
    if (LED_esp>=0) {
        now_millis = millis() % Pace_millis;
        if (now_millis > LED_millis*(slot-1) && now_millis < LED_millis*slot-LED_millis/2 ) {
            digitalWrite(LED_esp, boolean(config.LED));   // toggles LED status. will be restored by command below
            delay(LED_millis/2);
        }
    }
}

void flash_LED(unsigned int n_flash = 1) {
    if (LED_esp>=0) {
        for (size_t i = 0; i < n_flash; i++) {
            digitalWrite(LED_esp, boolean(config.LED));     // Turn LED on
            delay(LED_millis/3);
            digitalWrite(LED_esp, boolean(!config.LED));    // Turn LED off
            delay(LED_millis/3);
        }
    }
}

void Buzz(unsigned int n_beeps = 1) {                     // number of beeps 1 to 6 =>> 3000/500
    if (BUZZER>=0) {
        for (size_t i = 0; i < n_beeps; i++) {
            digitalWrite(BUZZER, HIGH);               // Turn Buzzer on
            delay(BUZZER_millis/6);
            digitalWrite(BUZZER, LOW);                // Turn Buzzer off
            delay(BUZZER_millis/6);
        }
    }
}


void hw_setup() {
  // Output GPIOs
      if (LED_esp>=0) {
          pinMode(LED_esp, OUTPUT);
          digitalWrite(LED_esp, LOW);                     // initialize LED off
      }
  // Input GPIOs

  // Start DHT device
      if (DHTPIN>=0) dht_val.begin();
}

void hw_loop() {
  // LED handling usefull if you need to identify the unit from many
      if (LED_esp>=0) digitalWrite(LED_esp, boolean(!config.LED));    // Values is reversed due to Pull-UP configuration
}
