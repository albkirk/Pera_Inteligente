#define discovery_prefix "homeassistant"

//JSON Variables
DynamicJsonDocument device_doc(128);
<<<<<<< HEAD
DynamicJsonDocument attributes_doc(384);
StaticJsonDocument<768> discovery_doc;
char device_jsonString[128];
char attributes_jsonString[384];
char discovery_jsonString[640];
=======
DynamicJsonDocument attributes_doc(256);
StaticJsonDocument<512> discovery_doc;
char device_jsonString[128];
char attributes_jsonString[256];
char discovery_jsonString[512];
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
int HASSIO_Fail = 0;                        // To count the MQTT messages that weren't sent. 
                                

String type[] =    {"button_short_press", "button_double_press", "button_triple_press", "button_quadruple_press", "button_quintuple_press"};
String payload[] = {"1", "2", "3", "4", "5"};
#define type_size 5

<<<<<<< HEAD
void hassio_device(String name = (String(config.DeviceName) + " " + String(config.Location) ), String ids = ChipID) {
=======
void hassio_device(String name = config.DeviceName, String ids = ChipID) {
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
    // device":{"name":"AmbiSense","identifiers":"09B376","manufacturer":"albroteam","model":"Ambiv2","sw_version":"01.01"}
    // Purge old JSON data and Load new values
    device_doc.clear();
    device_doc["name"]                  = name;                                 // Device friendly name
    device_doc["ids"]                   = ids;                                  // identifiers
<<<<<<< HEAD
=======
    //device_doc["cns"] = String("['IP','" + WiFi.localIP().toString() + "']"); // connections
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
    device_doc["mf"]                    = BRANDName;                            // manufacturer
    device_doc["mdl"]                   = MODELName;                            // model
    device_doc["sw"]                    = SWVer;                                // sw_version
}

<<<<<<< HEAD
void hassio_ids(String name = (String(config.DeviceName) + " " + String(config.Location) ), String ids = ChipID) {      // A short version of hassio_device
    device_doc.clear();
    //device_doc["name"]                  = name;                                 // Device friendly name
    device_doc["ids"]                   = ids;                                  // identifiers
=======
void trigger_discovery() {                                                      // NO longer in use... 
    String mqtt_pathhassio = String(discovery_prefix) + "/";

    device_doc.clear();
    device_doc["ChipID"]                = ChipID;                               // Chip identifier
    device_doc["DeviceName"]            = config.DeviceName;                    // Device friendly name
    device_doc["Location"]              = config.Location;                      // Device Location
    device_doc["sw"]                    = SWVer;                                // sw_version

    serializeJson(device_doc, device_jsonString);                                //Serialize JSON data to string
    //telnet_println("Trigger Discovery: " + String(device_jsonString));
    mqtt_publish(mqtt_pathhassio, "Discovery", String(device_jsonString), false);
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
}

void send_attributes(String param) {
    serializeJson(attributes_doc, attributes_jsonString);                       //Serialize JSON data to string
    //telnet_println("HASSIO Attributes: " + String(attributes_jsonString));
    mqtt_publish(mqtt_pathtele, String("attr_" + param), String(attributes_jsonString));
}


void send_status_attributes(String param) {
    attributes_doc.clear();
<<<<<<< HEAD
    attributes_doc["SWVer"]             = SWVer;                                // Software Version
    //attributes_doc["ChipID"]            = ChipID;                               // Chip ID
    //attributes_doc["CPUClock"]          = CPU_Clock();                          // CPU Clock
    attributes_doc["Boot"]              = ESPWakeUpReason();                    // Boot Reason
    if (WIFI_state == WL_CONNECTED) attributes_doc["IP"] = WiFi.localIP().toString(); // WiFi IP address
    #ifdef Modem_WEB_TELNET
        if (Celular_Connected) attributes_doc["IP"] = ModemIP;                  // Modem IP address
    #endif
    attributes_doc["Location"]          = config.Location;                      // Device Location
    attributes_doc["DEEPSleep"]         = config.DEEPSLEEP;                     // DEEPSleep status
    attributes_doc["ONTime"]            = config.ONTime;                        // ONTime 
    attributes_doc["SLEEPTime"]         = config.SLEEPTime;                     // DEEPSleep time

    #ifdef IP5306
        attributes_doc["Charging"]          = isCharging();                         // Batt charging
        attributes_doc["FullCharged"]       = isChargeFull();                       // Batt fully Charged
    #endif

    if (!BattPowered) {
        attributes_doc["APMode"]        = config.APMode;                        // APMode status
        attributes_doc["OTA"]           = config.OTA;                           // WEB status
        attributes_doc["WEB"]           = config.WEB;                           // WEB status
        attributes_doc["Telnet"]        = config.TELNET;                        // WEB status
=======
    attributes_doc["Boot"]              = ESPWakeUpReason();                    // Boot Reason
    attributes_doc["IP"]                = WiFi.localIP().toString();            // Device IP address
    attributes_doc["Location"]          = config.Location;                      // Device Location
    attributes_doc["DEEPSleep"]         = config.DEEPSLEEP;                     // DEEPSleep status
    attributes_doc["SLEEPTime"]         = config.SLEEPTime;                     // DEEPSleep time
    if (!BattPowered) {
        attributes_doc["APMode"]        = config.APMode;                        // APMode status
        attributes_doc["WEB"]           = config.WEB;                           // WEB status
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
        attributes_doc["WIFI_errors"]   = WIFI_errors;                          // WIFI errors
        attributes_doc["MQTT_errors"]   = MQTT_errors;                          // MQTT errors
        attributes_doc["NTP_errors"]    = NTP_errors;                           // NTP errors
    }
    send_attributes(param);
}

void send_switch_attributes(String param) {
    attributes_doc.clear();
    attributes_doc["auto_off_set"]      = TIMER;                                // auto_off_set
    attributes_doc["remaining_time"]    = TIMER_Current;                        // remaining_time
    send_attributes(param);
}

<<<<<<< HEAD

// HASSIO Configuration registration
// NOTE! entity and device_class must be lowecased, except "None"
// check for entity and device_class in https://www.home-assistant.io/integrations/mqtt/#mqtt-discovery
void config_entity(String entity, String device_class, String param = "", String device = "") {
    if(param == "") param = device_class;       // use the "device_class" as "param" value

    // Discovery Topic: // <discovery_prefix>/<entity>/[<node_id>/]<object_id>/config
    String mqtt_pathhassio;
    if (device == "Golf" || device == "Megane") mqtt_pathhassio = String(discovery_prefix) + "/" + entity + '/' + device + '-' + param + '/';
    else mqtt_pathhassio = String(discovery_prefix) + "/" + entity + '/' + ChipID.c_str() + '-' + param + '/';
    
    // Purge old JSON data and Load new values
    discovery_doc.clear();
    discovery_doc["~"]                  = mqtt_pathbase;        //defines the topic based Path 
=======
// HASSIO Configuration registration
void config_entity(String component = "sensor", String device_class = "Battery", String param = "", String device = "", String mqtt_path_stat = mqtt_pathtele) {
    //"sensor" have well defined classes: battery, humidity, illuminance, signal_strength, temperature, power, pressure, etc
    if(param == "") param = device_class;       // use the "device_class" as "param" value


    // Discovery Topic: // <discovery_prefix>/<component>/[<node_id>/]<object_id>/config
    String mqtt_pathhassio;
    if (device == "Golf" || device == "Megane") mqtt_pathhassio = String(discovery_prefix) + "/" + component + '/' + device + '-' + param + '/';
    else mqtt_pathhassio = String(discovery_prefix) + "/" + component + '/' + ChipID.c_str() + '-' + param + '/';
    
    // Purge old JSON data and Load new values
    discovery_doc.clear();
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
    if (device == "Golf" || device == "Megane") {
        discovery_doc["uniq_id"]        = device + '-' + param;
        discovery_doc["name"]           = device + ' ' + param;
    }
    else {
<<<<<<< HEAD
        discovery_doc["uniq_id"]        = ChipID + '_' + param;
        discovery_doc["name"]           = param.c_str();        // until 23.07 ChipID + ' ' + param;
    }

    if(entity == "sensor" && param == "Status") hassio_device();    //Only Status Sensor gets the device complete description
    else hassio_ids();
    discovery_doc["dev"]                = device_doc;


    if(entity == "cover") {
        if(device_class != "None") discovery_doc["device_class"] = device_class;// Device_class (ex.: shutter)
        discovery_doc["cmd_t"]          = "~/command/" + param;                 // command_topic
        discovery_doc["pos_t"]          = "~/inform/" + param;                  // position_topic
        discovery_doc["set_pos_t"]      = "~/command/" + param;                 // set_position_topic
        discovery_doc["pos_tpl"]        = "{{ value | int }}";
    }

    if(entity == "switch") {
        discovery_doc["stat_t"]         = "~/inform/" + param;                  // state_topic
        discovery_doc["cmd_t"]          = "~/command/" + param;                 // command_topic

        if(param == "LED") discovery_doc["icon"] = "hass:lighthouse-on";
        if(param == "Exterior") { 
            //discovery_doc["json_attr_t"] = "~/inform/" + "attr_" + param;     // Attributes topic
            discovery_doc["icon"]       = "hass:coach-lamp";
        }
        if(param == "Interior") { 
            //discovery_doc["json_attr_t"] = "~/inform/" + "attr_" + param;     // Attributes topic
            discovery_doc["icon"]       = "hass:ceiling-light";
        }
        if(param == "Socket") { 
            //discovery_doc["json_attr_t"] = "~/inform/" + "attr_" + param;     // Attributes topic
            discovery_doc["icon"]       = "hass:power-socket-fr";
        }
        if(param == "Switch" || param == "Switch2") { 
            //discovery_doc["json_attr_t"] = "~/inform/" + "attr_" + param;     // Attributes topic
            discovery_doc["icon"] = "hass:power";
        }
        if (param == "SpeedoMeter") { 
            discovery_doc["icon"] = "hass:car-cruise-control";
            discovery_doc["retain"]     = true;
        }
        //discovery_doc["stat_off"]     = "0";
        //discovery_doc["stat_on"]      = "1";
        discovery_doc["pl_off"]         = "0";                                  // Payload_off
        discovery_doc["pl_on"]          = "1";                                  // Payload_on
    }

    if(entity == "binary_sensor") {
        if(device_class != "None") discovery_doc["device_class"] = device_class;
        discovery_doc["stat_t"]         = "~/inform/" + param;                  // state_topic
        discovery_doc["pl_off"]         = "0";                                  // Payload_off
        discovery_doc["pl_on"]          = "1";                                  // Payload_on

    }

    if(entity == "sensor") {
        if(device_class != "None") discovery_doc["device_class"] = device_class;
        
        if (device == "PowerPlug" || device == "Telemetry") discovery_doc["stat_t"] = "~/inform/" + device;             // state_topic
        else discovery_doc["stat_t"]         = "~/inform/" + param;                             // state_topic
    
        if(param == "Status") discovery_doc["json_attr_t"] = "~/inform/attr_" + param;          // Attributes topic

        if(param == "Timer" || param == "Timer2") discovery_doc["icon"] = "hass:timer-outline";

        if(param == "Speed") {
            discovery_doc["unit_of_meas"] = "Km/h";
            discovery_doc["val_tpl"]      = "{{ value_json.Speed | float }}";
            discovery_doc["icon"]         = "hass:speedometer";
        }

        if(device_class == "battery") {
=======
        discovery_doc["uniq_id"]        = ChipID + '-' + param;
        discovery_doc["name"]           = ChipID + ' ' + param;
    }

//    discovery_doc["name"]               = ChipID + ' ' + param;
//    if(device == "") discovery_doc["name"] = config.Location;
//    else discovery_doc["name"]          = config.Location + String(' ') + param;
    discovery_doc["dev"]                = device_doc;

    if(component == "cover") {
        if(device_class != "none") discovery_doc["device_class"] = device_class;// Device_class (ex.: shutter)
        discovery_doc["cmd_t"]          = mqtt_pathcomd + param;                // command_topic
        discovery_doc["pos_t"]          = mqtt_path_stat + param;               // position_topic
        discovery_doc["set_pos_t"]      = mqtt_pathcomd + param;                // set_position_topic
        discovery_doc["val_tpl"]        = "{{ value | int }}";
    }

    if(component == "switch") {
        discovery_doc["stat_t"]         = mqtt_path_stat + param;               // state_topic
        discovery_doc["cmd_t"]          = mqtt_pathcomd + param;                // command_topic

        if(param == "LED") discovery_doc["icon"] = "hass:lighthouse-on";
        if(param == "Exterior") { 
            //discovery_doc["json_attr_t"] = mqtt_path_stat + "attr_" + param;    // Attributes topic
            discovery_doc["icon"]       = "hass:coach-lamp";
        }
        if(param == "Interior") { 
            //discovery_doc["json_attr_t"] = mqtt_path_stat + "attr_" + param;     // Attributes topic
            discovery_doc["icon"]       = "hass:ceiling-light";
        }
        if(param == "Socket") { 
            //discovery_doc["json_attr_t"] = mqtt_path_stat + "attr_" + param;     // Attributes topic
            discovery_doc["icon"]       = "hass:power-socket-fr";
        }
        if(param == "Switch" || param == "Switch2") { 
            //discovery_doc["json_attr_t"] = mqtt_path_stat + "attr_" + param;     // Attributes topic
            discovery_doc["icon"] = "hass:power";
        }
        //discovery_doc["stat_off"]     = "0";
        //discovery_doc["stat_on"]      = "1";
        discovery_doc["pl_off"]         = "0";                                      // Payload_off
        discovery_doc["pl_on"]          = "1";                                      // Payload_on
    }

    if(component == "binary_sensor") {
        if(device_class != "none") discovery_doc["device_class"] = device_class;
        discovery_doc["stat_t"]         = mqtt_path_stat + param;                   // state_topic
        discovery_doc["pl_off"]         = "0";                                      // Payload_off
        discovery_doc["pl_on"]          = "1";                                      // Payload_on

    }

    if(component == "sensor") {
        if(device_class != "none") discovery_doc["device_class"] = device_class;
        
        if (device == "PowerPlug") discovery_doc["stat_t"] = mqtt_path_stat + device;             // state_topic
        else discovery_doc["stat_t"]         = mqtt_path_stat + param;                            // state_topic
    
        if(param == "Status") discovery_doc["json_attr_t"] = mqtt_path_stat + "attr_" + param;    // Attributes topic

        if(param == "Timer" || param == "Timer2") discovery_doc["icon"] = "hass:timer-outline";

        if(device_class == "Battery" || device_class == "Humidity" || device_class == "illuminance") {
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
            discovery_doc["unit_of_meas"] = "%";
            discovery_doc["val_tpl"]      = "{{ value | float }}";
        }

        if(device_class == "signal_strength") {
            discovery_doc["unit_of_meas"] = "dBm";
            discovery_doc["val_tpl"]      = "{{ value | float }}";
            if(device == "Golf" || device == "Megane") discovery_doc["icon"] = "hass:bluetooth-audio";
            //discovery_doc["icon"]         = "hass:wifi";
        }

<<<<<<< HEAD
        if(device_class == "temperature") {
            discovery_doc["unit_of_meas"] = "°C";   // note the usage of char "°" and not "º" 
            discovery_doc["val_tpl"]      = "{{value_json.Temperature | float }}";
        }

        if(device_class == "humidity") {
            discovery_doc["unit_of_meas"] = "%";
            discovery_doc["val_tpl"]      = "{{ value_json.Humidity | float }}";
        }

        if(param == "HumVelocity") {
            discovery_doc["val_tpl"]      = "{{ value_json.HumVelocity | float }}";
        }

        if(device_class == "illuminance") {
            discovery_doc["unit_of_meas"] = "%";
            discovery_doc["val_tpl"]      = "{{ value_json.Illuminance | float }}";
        }

        if(device_class == "power") {
=======
        if(device_class == "Temperature") {
            discovery_doc["unit_of_meas"] = "ºC";
            discovery_doc["val_tpl"]      = "{{value | float }}";
        }

        if(device_class == "Power") {
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
            discovery_doc["unit_of_meas"] = "W";
            discovery_doc["val_tpl"]      = "{{value_json.Power | float }}";
            //discovery_doc["icon"]         = "hass:flash";
        }

<<<<<<< HEAD
        if(device_class == "voltage") {
=======
        if(device_class == "Voltage") {
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
            discovery_doc["unit_of_meas"] = "V";
            discovery_doc["val_tpl"]      = "{{value_json.Voltage | float }}";
            //discovery_doc["icon"]         = "hass:sine-wave";
        }

<<<<<<< HEAD
        if(device_class == "current") {
=======
        if(device_class == "Current") {
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
            discovery_doc["unit_of_meas"] = "A";
            discovery_doc["val_tpl"]      = "{{value_json.Current | float }}";
            //discovery_doc["icon"]         = "hass:triangle-wave";            
        }

<<<<<<< HEAD
        if(device_class == "energy") {
=======
        if(device_class == "Energy") {
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
            discovery_doc["unit_of_meas"] = "Wh";
            discovery_doc["val_tpl"]      = "{{value_json.Energy | float }}";
            discovery_doc["icon"]         = "hass:transmission-tower";
        }
    }

<<<<<<< HEAD
    if(entity == "light") {
        if(device_class != "None") discovery_doc["device_class"] = device_class;    // Device_class (ex.: shutter)
        discovery_doc["stat_t"]         = "~/inform/Light";                         // state_topic
        discovery_doc["pl_off"]         = "0";                                      // Payload_off
        discovery_doc["pl_on"]          = "1";                                      // Payload_on
        discovery_doc["cmd_t"]          = "~/command/Light";                        // command_topic
        discovery_doc["rgb_stat_t"]     = "~/inform/Color";                         // rgb_state_topic
        discovery_doc["rgb_cmd_t"]      = "~/command/Color";                        // rgb_command_topic
        discovery_doc["rgb_val_tpl"]    = "{{(int(value[1:3], base=16), int(value[3:5],base=16), int(value[5:7],base=16)) | join(',')}}";   // rgb_value_template
        discovery_doc["bri_stat_t"]     = "~/inform/Gain";                          // brightness_state_topic
        discovery_doc["bri_cmd_t"]      = "~/command/Gain";                         // brightness_command_topic
        discovery_doc["fx_stat_t"]      = "~/inform/EFX";                           // effect_state_topic
        discovery_doc["fx_cmd_t"]       = "~/command/EFX";                          // effect_command_topic
        JsonArray effects = discovery_doc.createNestedArray("fx_list");
            effects.add("NoEFX");
            effects.add("Auto");
            effects.add("Flash");
            effects.add("Fade3");
            effects.add("Fade7");
            effects.add("scan");
            effects.add("Rainbow");
        //discovery_doc["fx_list"]        = "['NoEFX','Auto','Flash','Fade3','Fade7','scan','Raibow']"; // effect_list
        //discovery_doc["fx_list_tpl"]    = "{{ value | list }}";                     //effect_value_template
        //effect_command_topic
        // state_topic: "office/rgb1/light/status"
        // command_topic: "office/rgb1/light/switch"
        // brightness_state_topic: "office/rgb1/brightness/status"
        // brightness_command_topic: "office/rgb1/brightness/set"
        // rgb_state_topic: "office/rgb1/rgb/status"
        // rgb_command_topic: "office/rgb1/rgb/set"
        // state_value_template: "{{ value_json.state }}"
        // brightness_value_template: "{{ value_json.brightness }}"
        // rgb_value_template: "{{ value_json.rgb | join(',') }}"

    }
/*
'rgb_cmd_t':           'rgb_command_topic',
'rgb_cmd_tpl':         'rgb_command_template',
'rgb_stat_t':          'rgb_state_topic',
'rgb_val_tpl':         'rgb_value_template',
'bri_cmd_t':           'brightness_command_topic',
'bri_cmd_tpl':         'brightness_command_template',
'bri_scl':             'brightness_scale',
'bri_stat_t':          'brightness_state_topic',
'bri_tpl':             'brightness_template',
'bri_val_tpl':         'brightness_value_template',
*/



=======
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
    serializeJson(discovery_doc, discovery_jsonString);                     //Serialize JSON data to string
    //telnet_println("HASSIO Config: " + String(discovery_jsonString));
    if(!mqtt_publish(mqtt_pathhassio, "config", String(discovery_jsonString), true)) HASSIO_Fail ++;
}


<<<<<<< HEAD
void delete_entity(String entity = "sensor", String device_class = "battery", String param = "", String device = "") {
    if(param == "") param = device_class;       // use the "device_class" as "param" value

    String mqtt_pathhassio;
    if (device == "Golf" || device == "Megane") mqtt_pathhassio = String(discovery_prefix) + "/" + entity + '/' + device + '-' + param + '/';
   else mqtt_pathhassio = String(discovery_prefix) + "/" + entity + '/' + ChipID.c_str() + '-' + param + '/';
=======
void delete_entity(String component = "sensor", String device_class = "Battery", String param = "", String device = "") {
    if(param == "") param = device_class;       // use the "device_class" as "param" value

    String mqtt_pathhassio;
    if (device == "Golf" || device == "Megane") mqtt_pathhassio = String(discovery_prefix) + "/" + component + '/' + device + '-' + param + '/';
   else mqtt_pathhassio = String(discovery_prefix) + "/" + component + '/' + ChipID.c_str() + '-' + param + '/';
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6

    mqtt_publish(mqtt_pathhassio, "config", "", true);
}


void config_trigger(String subtype = "Button_1", String param = "") {
    // subtype => ["button_1", "button_2", "button_3", "button_4", "button_5", "button_6"]

    if(param == "") param = subtype;       // use the "device_class" as "device" value

    String mqtt_pathhassio;

    for (size_t i = 0; i < type_size; i++)
    {
        // <discovery_prefix>/device_automation/[<node_id>/]<object_id>/config
        mqtt_pathhassio = String(discovery_prefix) + "/" + "device_automation" + '/' + ChipID.c_str() + '/' + subtype + '-' + type[i] + '/';

    
        // Purge old JSON data and Load new values
        discovery_doc.clear();
        discovery_doc["dev"]                = device_doc;

        discovery_doc["atype"]              = "trigger";                            // automation_type
        discovery_doc["topic"]              = mqtt_pathtele + param;
        discovery_doc["type"]               = type[i];
        discovery_doc["subtype"]            = subtype;
        discovery_doc["payload"]            = payload[i];

        serializeJson(discovery_doc, discovery_jsonString);                     //Serialize JSON data to string
        //telnet_println("HASSIO Config: " + String(discovery_jsonString));
        if(!mqtt_publish(mqtt_pathhassio, "config", String(discovery_jsonString), true)) HASSIO_Fail ++;
        yield();
    }

}


void delete_trigger(String subtype = "Button_1", String param = "") {
    // subtype => ["button_1", "button_2", "button_3", "button_4", "button_5"]  "button_6" is reserved for BOOT message!
    String mqtt_pathhassio;

    if(param == "") param = subtype;       // use the "device_class" as "device" value

    for (size_t i = 0; i < type_size; i++)
    {
        // <discovery_prefix>/device_automation/[<node_id>/]<object_id>/config
        mqtt_pathhassio = String(discovery_prefix) + "/" + "device_automation" + '/' + ChipID.c_str() + '/' + subtype + '-' + type[i] + '/';

        mqtt_publish(mqtt_pathhassio, "config", "", true);
    }

}




#include <custohassio.h>

void hassio_discovery() {
    HASSIO_Fail = 0;
<<<<<<< HEAD
    config_entity("sensor", "None", "Status");
    //delay(10); send_status_attributes("Status");          // dont' need to execute here because this is done later
    if (BattPowered) config_entity("sensor", "battery", "Battery");
    else delete_entity("sensor", "battery", "Battery");
    if (LED_ESP>=0) config_entity("switch", "switch", "LED");
    config_entity("sensor", "signal_strength", "RSSI");
=======
    hassio_device();
    config_entity("sensor","none", "Status");
    //delay(10); send_status_attributes("Status");          // dont' need to execute here because this is done later
    if (BattPowered) config_entity("sensor","Battery");
    else delete_entity("sensor","Battery");
    if (LED_ESP>=0) config_entity("switch", "none", "LED");
    config_entity("sensor","signal_strength", "RSSI");
    //config_trigger_boot();                                // not used
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
    custo_hassio_disc();
    if (HASSIO_Fail == 0 ) {
        config.HASSIO_CFG = true;
        storage_write();
    }
<<<<<<< HEAD
    else telnet_println("Discovery Error! -> HASSIO_Fail = " + String(HASSIO_Fail));
}

void hassio_delete() {
    delete_entity("sensor", "None", "Status");
    delete_entity("sensor", "battery", "Battery");
    delete_entity("switch", "switch", "LED");
    delete_entity("sensor", "signal_strength", "RSSI");
=======
}

void hassio_delete() {
    hassio_device();
    delete_entity("sensor","none", "Status");
    delete_entity("sensor","Battery");
    delete_entity("switch", "none", "LED");
    delete_entity("sensor","signal_strength", "RSSI");
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
    //delete_trigger_boot();                                // not used
    custo_hassio_del();
    config.HASSIO_CFG = false;
    storage_write();
}

void hassio_attributes() {
    //delay(10);
    send_status_attributes("Status");
    custo_hassio_attr();
}
