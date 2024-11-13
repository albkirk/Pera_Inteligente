<<<<<<< HEAD
// WRITE HERE all the Project's logic / Flow.
// **** Libraries to include here ...
=======
// **** Project code definition here ...
//#include <flash.h>
//#include <ambient.h>


>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6

// **** Project code definition here ...

// **** Project code functions here ...
<<<<<<< HEAD
void project_setup() {
=======
void project_hw() {
 // Output GPIOs


 // Input GPIOs

    //flash_setup();                                // Required for telemetry storage in Flash
}


void project_setup() {
    mqtt_publish(mqtt_pathtele, "Button", "1");      
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
}

void project_loop() {
  // Ambient handing
      //if (TIMER >0) if ((millis() - 3500) % (TIMER * 60000) < 5) ambient_data();      // TIMER bigger than zero on div or dog bites!!
<<<<<<< HEAD
=======

>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
}
