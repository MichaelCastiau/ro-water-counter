# RO Water Counter
<img alt="Screenshot 2022-12-10 at 11 30 11" src="https://user-images.githubusercontent.com/10990692/206850769-03a02047-d70c-4bf7-80f0-054f305e1426.png"> 

This repository contains the source code and hardware schematics for a Reverse Osmosis water counter device, based on an ESP32 module. The device allows for setting an amount of needed liters of water an will swich on/off the RO system automatically. When the amount of liters needed has been reached, the ESP32 module is programmed to interact with a webhook to send a notification to your smartphone.

It interfaces with a high-precision water flow sensor with a K-factor of 20.

<img height=500 src="https://user-images.githubusercontent.com/10990692/206850772-1a3cd72d-baa5-4b9a-8313-d5b7e3b0403e.PNG">

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

The application itself should be flashed at address 0x10000 (or 0x210000 if using OTA), corresponding to the address defined in the bootloader table.

```shell
python -m esptool  --port /dev/tty.usbmodem14301 --chip esp32 write_flash 0x10000 .pio/build/default/firmware.bin
```
