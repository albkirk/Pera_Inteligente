import time
import sys

Batt_Max_def = 4.1
Batt_Min_def = 2.8
Vcc_def      = 3.3
"""
#define Batt_Max float(4.1)                 // Battery Highest voltage.  [v]
#define Batt_Min float(2.8)                 // Battery lowest voltage.   [v]
#define Vcc float(3.3)                      // Theoretical/Typical ESP voltage. [v]
"""

def main():     
    print("H3llo World")
    voltage = ''
    while (voltage == '') :
        voltage = input(' - - ENTER Voltage value:  ')
        if (voltage == ''): print("You must enter a number")
    Batt_Max = input(' - - ENTER Batt_Max value[%f]:  ' %(Batt_Max_def))
    if (Batt_Max == ''): Batt_Max = Batt_Max_def
    Batt_Min = input(' - - ENTER Batt_Min value[%f]:  ' %(Batt_Min_def))
    if (Batt_Min == ''): Batt_Min = Batt_Min_def
    batt_level = ((float(voltage) - float(Batt_Min)) / (float(Batt_Max) - float(Batt_Min))) * 100.0
    print("Battery Level: %f" %(batt_level))

    input(' - - Press ENTER to close - - ')
    #sys.exit()


if __name__ == '__main__':

    while True:
        main()