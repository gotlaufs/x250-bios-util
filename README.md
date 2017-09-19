# Lenovo ThinkPad x250 BIOS chip utility

This utility is for reading/writing Winbond W25Q128 BIOS EEPROM chip found on
Lenovo ThinkPad  x250 laptop. The current implementation uses RaspberryPi as a
SPI reader/writer.

## Usage
 - Install current version of [wiringPi](http://wiringpi.com/) library.
 - Use `make` to compile project
 - Solder wires to BIOS chip and attach them to Raspberry Pi's SPI pins
 - Execute `bin/x250_util`

## Ports

This program should run on any linux machine as long as you can provide a SPI
interface. Modify `ports.c` for your device and you should be good to go!

## Issues

 - This software uses a very small SPI buffer of 2 kB that make reading and writing
of the chip quite slow. You can modify Raspberry's
[kernel parameters](https://stackoverflow.com/questions/16427996/increase-spi-buffer-size-in-raspbian) to increase SPI buffer size:   
Add `spidev.bufsiz=<NEEDEDBUFFER SIZE>` to `cmdline.txt`.

 - RaspberryPi's GPIOs are quite weak and you may need to use a voltage buffer on
SPI MOSI, MISO, CLK and CS pins to get reliable operation.

## More documentation

Look into `docs` for datasheet of the W25Q128, RaspberryPi's header pinout and
connection scheme.
