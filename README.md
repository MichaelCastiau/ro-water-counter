# RO Water Counter

This repository contains the source code and hardware schematics for a Reverse Osmosis water counter device, based on an ESP32 module. The device allows for setting an amount of needed liters of water an will swich on/off the RO system automatically. When the amount of liters needed has been reached, the ESP32 module is programmed to interact with a webhook to send a notification to your smartphone.

It interfaces with a water flow sensor type YF-S401. The sensor has a K-factor of 56. (Wrongly stated as 73 on the datasheet).

## Flashing

```shell
python -m esptool  --port /dev/tty.usbserial-1420 --chip esp32 write_flash 0x00010000 .pio/build/esp32/firmware.bin
```
### Bootloader

The ESP32 requires a second stage bootloader that will read the partition table and boot the corresponding app.
The booloader is located in the `bootloader.bin` file and should be flashed at address 0x1000 in the flash.

```shell
python -m esptool  --port /dev/tty.usbmodem14301 --chip esp32 write_flash 0x1000 bootloader.bin
```

### Partition Table

This project utilises a custom partition table to make enough room for OTA updates.
The partition definitions can be found in `partitions.csv` file. The partition table should be flashed
at address 0x8000 in  the flash after building the project with PlatformIO.


```shell
python -m esptool  --port /dev/tty.usbmodem14301 --chip esp32 write_flash 0x8000 .pio/build/default/partitions.bin
```

### Application

The applicatino itself should be flashed at address 0x10000, corresponding to the address defined in the bootloader table.

```shell
python -m esptool  --port /dev/tty.usbmodem14301 --chip esp32 write_flash 0x10000 .pio/build/default/firmware.bin
```
