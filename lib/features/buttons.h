#define BUTTONS_H true

<<<<<<< HEAD
void IRAM_ATTR A_pressed ();
void IRAM_ATTR B_pressed ();
void IRAM_ATTR C_pressed ();

// **** Normal code definition here ...
//#define BUT_A -1                  // Button A INPUT pin. Configure in "def_conf.h"
//#define BUT_B -1                  // Button B INPUT pin. Configure in "def_conf.h"
//#define BUT_C -1                  // Button C INPUT pin. Configure in "def_conf.h"
=======
void ICACHE_RAM_ATTR A_pressed ();
void ICACHE_RAM_ATTR B_pressed ();
void ICACHE_RAM_ATTR C_pressed ();


// **** Normal code definition here ...
#define BUT_A 13                    // Button A INPUT pin
#define BUT_B -1                    // Button B INPUT pin
#define BUT_C -1                    // Button C INPUT pin
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
#define Butt_Bounce_Time 25         // time interval window to ignore bouncing
#define Butt_Interval 500           // time interval window to count buttons pushes
static bool A_STATUS = false;       // status of button A (true = pressed, false = released)
static bool B_STATUS = false;       // status of button B (true = pressed, false = released)
static bool C_STATUS = false;       // status of button C (true = pressed, false = released)
static int A_COUNT = 0;             // to count number of times button A is pressed within interval
static int B_COUNT = 0;             // to count number of times button B is pressed within interval
static int C_COUNT = 0;             // to count number of times button C is pressed within interval
static uint32_t Last_A = 0;         // timer var to avoid function call trigger due contact bounce
static uint32_t Last_B = 0;         // timer var to avoid function call trigger due contact bounce
static uint32_t Last_C = 0;         // timer var to avoid function call trigger due contact bounce

// BUTTON related functions
void A_pressed () {
  detachInterrupt(BUT_A);                            // to avoid this function call be retriggered (or watch dog bites!!)
  unsigned long NOW = millis();
  if (NOW - Last_A > Butt_Bounce_Time) {                 // respect minimum time between 2 consecutive function calls
      while (millis() - NOW < Butt_Bounce_Time) {};      // loop to allow button status be stable before reading it
      if (digitalRead(BUT_A) == LOW) {
          A_STATUS = true;
          if (NOW - Last_A < Butt_Interval) {
              A_COUNT += 1;
<<<<<<< HEAD
              telnet_println("Button A pressed " + String(A_COUNT) + " times!");
          }
          else {
              A_COUNT = 1;
              telnet_println("Button A pressed");
=======
              Serial.println("Button A pressed " + String(A_COUNT) + "times!");
          }
          else {
              A_COUNT = 1;
              Serial.println("Button A pressed");
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
          };
      }
      else {
          A_STATUS = false;
<<<<<<< HEAD
          telnet_println("Button A released");
=======
          Serial.println("Button A released");
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
      };
  }
  Last_A = NOW;
  attachInterrupt(BUT_A, A_pressed, CHANGE);
}

void B_pressed () {
  detachInterrupt(BUT_B);                            // to avoid this function call be retriggered (or watch dog bites!!)
  unsigned long NOW = millis();
  if (NOW - Last_B > Butt_Bounce_Time) {                 // respect minimum time between 2 consecutive function calls
      while (millis() - NOW < Butt_Bounce_Time) {};      // loop to allow button status be stable before reading it
      if (digitalRead(BUT_B) == LOW) {
          B_STATUS = true;
          if (NOW - Last_B < Butt_Interval) {
              B_COUNT += 1;
<<<<<<< HEAD
              telnet_println("Button B pressed " + String(B_COUNT) + " times!");
          }
          else {
              B_COUNT = 1;
              telnet_println("Button B pressed");
=======
              Serial.println("Button B pressed " + String(B_COUNT) + "times!");
          }
          else {
              B_COUNT = 1;
              Serial.println("Button B pressed");
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
          };
      }
      else {
          B_STATUS = false;
<<<<<<< HEAD
          telnet_println("Button B released");
=======
          Serial.println("Button B released");
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
      };
  }
  Last_B = NOW;
  attachInterrupt(BUT_B, B_pressed, CHANGE);
}

void C_pressed () {
  detachInterrupt(BUT_C);                            // to avoid this function call be retriggered (or watch dog bites!!)
  unsigned long NOW = millis();
  if (NOW - Last_C > Butt_Bounce_Time) {                 // respect minimum time between 2 consecutive function calls
      while (millis() - NOW < Butt_Bounce_Time) {};      // loop to allow button status be stable before reading it
      if (digitalRead(BUT_C) == LOW) {
          C_STATUS = true;
          if (NOW - Last_C < Butt_Interval) {
              C_COUNT += 1;
<<<<<<< HEAD
              telnet_println("Button C pressed " + String(C_COUNT) + " times!");
          }
          else {
              C_COUNT = 1;
              telnet_println("Button C pressed");
=======
              Serial.println("Button C pressed " + String(C_COUNT) + "times!");
          }
          else {
              C_COUNT = 1;
              Serial.println("Button C pressed");
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
          };
      }
      else {
          C_STATUS = false;
<<<<<<< HEAD
          telnet_println("Button C released");
=======
          Serial.println("Button C released");
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
      };
  }
  Last_C = NOW;
  attachInterrupt(BUT_C, C_pressed, CHANGE);
}

<<<<<<< HEAD
void buttons_setup() {
  if (BUT_A>=0) {
        pinMode(BUT_A, INPUT_PULLUP);
        A_STATUS = !bool(digitalRead(BUT_A));
=======

void buttons_setup() {
  if (BUT_A>=0) {
        pinMode(BUT_A, INPUT_PULLUP);
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
        attachInterrupt(BUT_A, A_pressed, CHANGE);
  }
  if (BUT_B>=0) {
        pinMode(BUT_B, INPUT_PULLUP);
<<<<<<< HEAD
        B_STATUS = !bool(digitalRead(BUT_B));
=======
>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
        attachInterrupt(BUT_B, B_pressed, CHANGE);
  }
  if (BUT_C>=0) {
        pinMode(BUT_C, INPUT_PULLUP);
<<<<<<< HEAD
        C_STATUS = !bool(digitalRead(BUT_C));
        attachInterrupt(BUT_C, C_pressed, CHANGE);
  }
=======
        attachInterrupt(BUT_C, C_pressed, CHANGE);
  }

>>>>>>> a229e5ec3f4b409bfe93b378e072607fe225e6c6
}
