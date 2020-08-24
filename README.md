# Intro
A simple CO2 display using the MH-Z19 sensor

![Example Setup](https://raw.githubusercontent.com/kiu/simple-co2/master/simple-co2-02.jpg)

# BOM

Item | Link | Price
---- | ---- | -----
Arduino Nano | https://www.amazon.de/AZDelivery-Atmega328-gratis-Arduino-kompatibel/dp/B01LWSJBTD/ | 6.49 €
Sensor MH-Z19 | https://www.amazon.de/gp/product/B07VD15YRP/ | 32.99 €
LED Matrix | https://www.amazon.de/AZDelivery-MAX7219-Matrix-Anzeigemodul-Arduino/dp/B079HVW652/ | 8.99 €
Jumper Wire | https://www.amazon.de/AZDelivery-Jumper-Arduino-Raspberry-Breadboard/dp/B074P726ZR/ | 4.99 €
USB Power (1A/5W) | https://www.amazon.de/HomeSpot-kompaktes-Universal-Ladegerät-Netzteil/dp/B01DIYZTKK/ | 6.99 €
USB Breakout | https://www.amazon.de/WayinTop-Breakout-Konverter-Netzteil-Steckbrett/dp/B07W13X3TD/ | 6.99 €
Mini USB Cable | https://www.amazon.de/PremiumCord-Kabel-USB-B-Mini-5pins/dp/B07NSMMVB2/ | 1.78 €


# Wiring

https://content.arduino.cc/assets/NanoV3.3_sch.pdf

LED Matrix | Arduino Nano
---------- | ------------
VCC | ISCP2 / +5V (4)
GND | ISCP6 / GND (2)
DIN | ICSP4 / D11  MOSI (14)
CS | D7 (10)
CLK | ICSP3 / D13 SCK (15)

MH-Z19 | Arduino Nano
------ | ------------
VCC (6) | ISCP2 / +5V (4)
GND (7) | ISCP6 / GND (2)
TX (3) | D0 RX (2)
RX (2) | D1 TX (1)

USB Breakout | Arduino Nano
------------ | ------------
VCC | ISCP2 / +5V (4)
GND | ISCP6 / GND (2)
 
