![bugdroid](https://raw.githubusercontent.com/rk4an/bugdroid-blink/master/img/bugdroid.jpg)

## Prerequisite ##

* [Arduino Nano with ATMEGA328P][2]
* [Bluetooth HC-06][3]
* 2 green LEDs
* 2 resitors 220 Ohm
* A bugdroid

## Installation ##

* Led right on pin D3
* Led left on pin D4
* HC-06 TX on D6 and RX on D7

  [1]: https://play.google.com/store/apps/details?id=mobi.dzs.android.BLE_SPP_PRO&hl=fr_FR
  [2]: http://www.amazon.fr/gp/product/B00D84UN9S/
  [3]: http://www.amazon.fr/gp/product/B00H07UJL6/

## Usage ##

  * Android: [Bluetooth SPP Pro apps][1]
  * Linux: 
    * sudo hcitool scan
    * sudo rfcomm bind /dev/rfcomm0 xx:xx:xx:xx:xx:xx 1
