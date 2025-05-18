# Pera Inteligente - Smart BedSide Cord Switch

This project builds a small portable device that switches (ON/OFF) the light of the (bed)room when its unique push button is pressed.
This is the 21st version of the older bedside cord switch used to operate the ceiling light from the comfort of the warm bed. : )

![Pera](Documents/Pera.jpg)

The "smart" part of the project is just have it sending BT beacons, which are then captured and processed by an external entity, that will, de facto, select the right appliance to instruct for ON/OFF switching.

##
## --Hardware--

This device is based on Espressif **ESP32-C3** MCU.

The only physical operational interface available is a simple **Push Button** to wake up the MCU (RST to GND shunt).

As it is battery-powered, the MCU is kept in sleep mode as much as possible and is only woken to announce its presence. To reduce the size, it is powered by a small **200mAh** Lithium-Ion battery. The **Batt Charger** circuit is the compact module [Type-C USB TP4056 1A Lithium Battery Charging Protection] (https://www.aliexpress.com/item/1005004987359215.html), fitted internally.


##
## --Software--

Being based on my [GitHub albkirk ESP-KickStart](https://github.com/albkirk/ESP-KickStart) template, which already included all the code required for:

- Configurable Deep Sleep,
- Battery Level monitoring,
- Telnet debugging text output.
- Wi-Fi WLAN network connectivity with Static IP addressing.
- MQTT registration, data subscription and publishing,
- Remote upgrade via OTA.

##
## --Case--

- [Main Body](Documents/Pera%20Body.stl)
- [Cover](Documents/Pera%20Cover.stl)


<img src="Documents/Foto%20Display.jpg" alt="Foto Display" style="width: 33%;">

<img src="Documents/Inside.png" alt="Complete Wiring" style="width: 50%;">