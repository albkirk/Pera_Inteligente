/*
 * * Main File to trigger all C code using "arduino" style.
 * * It contains all necessary function calls on setup and loop functions
 * * HOW TO USE THIS TEMPLATE:
 * * -- Adjust the parameter below to your project.
 * *    Parameters on struct "config" will be store on memory.
 * *    Don't forget to customize the Mem read and write actions on "lib/project/custostore.h"
 * * -- Use the "// **** Normal code ..." zones to add you own definition, functions, setup and loop code
 * * -- You can also add you own MQTT actions on "lib/project/customqtt.h"
 * * -- Suggest to use "lib/project/" to add your own h files
 */

// Libraries to INCLUDE
#include <storage.h>

#ifdef ESP32
    #include <esp32hw.h>
#else 
    #include <hw8266.h>
#endif

#include <mywifi.h>
<<<<<<< HEAD

//#ifdef ESP8266
//    #include <httpupd.h>
//#endif

#include <console.h>
#include <ntp.h>
#include <mqtt.h>
=======
#include <httpupd.h>
#include <telnet.h>
#include <ntp.h>
#include <mqtt.h>
#include <hassio.h>
#include <ota.h>
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
#include <global.h>
#include <peripherals.h>
#include <hassio.h>
#include <ota.h>
#ifndef ESP8285
    #include <web.h>
#endif
#include <project.h>
<<<<<<< HEAD
#include <actions.h>                        // Added later because functions from project are called here.


void setup() {
  // Starting with WiFi interface shutdown in order to save energy
    wifi_disconnect();

  // Start SERIAL console
      //Serial.begin(74880);                  // This odd baud speed will shows ESP8266 boot diagnostics too.
      Serial.begin(115200);                 // For faster communication use 115200
      //Serial.setTimeout(1000);
=======
#include <web.h>
#include <mqttactions.h>                                // Added later because functions from project are called here.


void setup() {
// Starting with WiFi interface shutdown in order to save energy
    wifi_disconnect();

  // Start Serial interface
      Serial.begin(74880);                  // This odd baud speed will shows ESP8266 boot diagnostics too.
      //Serial.begin(115200);               // For faster communication use 115200
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6

      Serial.println("");
      Serial.println("Hello World!");
      Serial.println("My ID is " + ChipID + " and I'm running version " + SWVer);
      Serial.println("Reset reason: " + ESPWakeUpReason());

  // Start Storage service and read stored configuration
      storage_setup();

  // Start Global features, such as: ESP_LED, Buzzer, internal ADC, ...
      global_setup();

  //  Project peripherals initialization, such as: GPIO config, Sensors, Actuators, ...  
      peripherals_setup();

  // Start WiFi service (Station or/and as Access Point)
      wifi_setup();
    
  // Check for HTTP Upgrade
      http_upg();               // Note: this service kills all running UDP and TCP services

  // Check for HTTP Upgrade
//#ifdef ESP8266
//      http_upg();               // Note: this service kills all running UDP and TCP services
//#endif
  // Start TELNET console service
      telnet_setup();

<<<<<<< HEAD
 // Start MQTT service
      mqtt_setup();

  // Start OTA service
      ota_setup();

  // Start NTP service
      ntp_setup();

#ifndef ESP8285
  // Start ESP Web Service
      if (config.WEB) web_setup();
#endif
=======
  // Start NTP service
      ntp_setup();

 // Start MQTT service
      mqtt_setup();

  // Start OTA service
      if (config.OTA) ota_setup();

  // Start ESP Web Service
      if (config.WEB) web_setup();
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6

  // **** Project SETUP Sketch code here...
      project_setup();

<<<<<<< HEAD
  // with all setup tasks done it's time to prompt!
      console_prompt();

  // Last bit of code before leave setup
      ONTime_Offset = millis() + 200UL;     //  200ms after finishing the SETUP function it starts the "ONTime" countdown.
=======
  // Last bit of code before leave setup
      ONTime_Offset = millis() + 100UL;     //  100ms after finishing the SETUP function it starts the "ONTime" countdown.
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
                                            //  it should be good enough to receive the MQTT "ExtendONTime" msg
} // end of setup()


void loop() {
  // allow background process to run.
      yield();

  // Global handling, namely the button to return to default configuration
      //global_loop();

  // WiFi handling
      wifi_loop();

  // Serial handling
      serial_loop();

  // TELNET handling
      if (config.TELNET) telnet_loop();

<<<<<<< HEAD
=======
  // NTP handling
      ntp_loop();

>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
  // MQTT handling
      mqtt_loop();

  // OTA request handling
      if (config.OTA) ota_loop();

<<<<<<< HEAD
  // NTP handling
      ntp_loop();

#ifndef ESP8285
  // ESP Web Server requests handling
      if (config.WEB) web_loop();
#endif
=======
  // ESP Web Server requests handling
      if (config.WEB) web_loop();
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6

  // **** Project LOOP Sketch code here ...
      project_loop();

  // Global loops handling
      deepsleep_loop();
      if (BattPowered && ((millis() - 3500) % 60000 < 5)) Batt_OK_check();    // If Batt LOW, it will DeepSleep forever!

}  // end of loop()
