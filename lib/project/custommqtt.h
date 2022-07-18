// Function to insert customized MQTT Configuration actions
void custom_mqtt(String command, String cmd_value) {
  if ( command == "Info" && bool(cmd_value.toInt())) {
    //status_report();
    if (BattPowered) mqtt_publish(mqtt_pathtele, "Battery", String(getBattLevel(),0));
    mqtt_publish(mqtt_pathtele, "NTP_Sync", String(NTP_Sync));
    mqtt_publish(mqtt_pathtele, "DateTime", String(curDateTime()));
    hassio_attributes();
    //ambient_data();
  }
  if ( command == "Config" && bool(cmd_value.toInt())) {
    mqtt_publish(mqtt_pathtele, "OTA", String(config.OTA));
    mqtt_publish(mqtt_pathtele, "TELNET", String(config.TELNET));
    mqtt_publish(mqtt_pathtele, "WEB", String(config.WEB));
    mqtt_publish(mqtt_pathtele, "Interval", String(config.SLEEPTime));   
    mqtt_publish(mqtt_pathtele, "Temp_Corr", String(config.Temp_Corr));
    mqtt_publish(mqtt_pathtele, "LDO_Corr", String(config.LDO_Corr));
    config_backup();
  }


  if ( command == "BckpRstr") {
      if (cmd_value == "") telnet_println("Restore data is empty");
      else {
          DeserializationError error = deserializeJson(config_doc, cmd_value); //Deserialize string to JSON data
          if (error) {telnet_print("JSON DeSerialization failure: "); telnet_println(error.f_str());}
          else {

                strcpy(config.Location, config_doc["Location"]);
/*
                config.LOWER_LEVEL =    config_doc["LOWER_Pos"];
                config.UPPER_LEVEL =    config_doc["UPPER_Pos"];
*/
                storage_write();
                hassio_attributes();
                bckup_rstr_flag = false;
          }
      }
  }
}

void custom_update(){
    yield();
//    mqtt_dump_data(mqtt_pathtele, "Telemetry");
}
