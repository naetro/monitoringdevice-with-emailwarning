##Arduino based monitoring device with an email alert

A monitoring device that monitors temperature and motion. The device also sends out an email alert, using Temboos Gmail choreo.


##Requirements

* Arduino Yún
* Parallax PIR sensor
* TMP36 analog temperature sensor
* Breadboard
* Some male/male and female/male jumper wires
* Temboo account
* Gmail account


##Wiring

PIR sensor:
VCC to 5V
GND to GND
OUT to digital 2

Temperature sensor:
Power up the breadboard with 3.3V pin
Connect AREF pin to + on the breadboard's power bus 

Attach the sensor to breadboard
Connect the left pin (facing the flat side) of the sensor to power 
Connect the right pin (facing the flat side) of the sensor to ground
Connect the middle pin (facing the flat side) of the sensor to analog 1 

![Wiring](https://github.com/naetro/monitoringdevice-with-emailwarning/blob/master/pictures/pirtemp_fritzin_edited2.jpg)


## Setting up

The main sketch references the TembooAccount.h header file, so you need to make a new tab beside the main sketch and name it TembooAccount.h. The header file contains some Temboo account information. You can find your individual header information at Temboos site, once you're logged in. e.g https://temboo.com/arduino/yun/send-an-email. 
