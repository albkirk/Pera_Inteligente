// **** Project code definition here ...
#include <ambient.h>


// **** Project code functions here ...
void find_ESPs() {
    uint search_ch = rtcData.LastWiFiChannel;
    String ESP_AP_list = "";
    for (uint i = 0; i < 13; i++) {
        wifi_sniffer(search_ch, search_ch);
        ESP_AP_list = wifi_listSTAs();
        telnet_println("AP List: " + ESP_AP_list);
        if (ESP_AP_list.substring(0,ESP_AP_list.length()) == config.ssid){
            mqtt_publish(mqtt_pathtele(), "Status", ESP_AP_list);
            break;
        }
        else search_ch ++;
    }
}


void project_hw() {
 // Output GPIOs


 // Input GPIOs

}


void project_setup() {
  // Start Ambient devices
      //ambient_setup();

}

void project_loop() {
  // Ambient handing
      //if ((millis() - 3500) % (TIMER * 60000) < 15) ambient_data();      // Every TIMER (15) minutes

}
