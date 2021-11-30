# Example Collection General Rules

## Android

### Flutter
- Only pubspec.yaml file and lib folder

#### List Examples
- Serial Terminal

## Embedded

### ATMega
- No Arduino source-code
- Only Eagle or KiCAD as PCB design
- Only C, CPP, or Makefile as sources
- Simulation only Simulide or open-sources sims

#### List Examples
- adc_lcd_uart
- atmega_tacho
- AVRCppBook
- car_control
- cerdas_cermat
- input_capture
- las_orbit
- m128_adc_hmi_mmc
- m128_fatfs_qt
- rpm_lcd
- sonic_range
- tacho
- voltmeter

### ESP8266
- No Arduino source-code
- Only Eagle or KiCAD as PCB design
- Only C, CPP, or Makefile as sources
- Only sources without library packages
- Non ESP-RTOS must in a dedicated folder

#### List Examples
- blink_console
- Non ESP-RTOS
	+ blink_led0
	+ blink_led1
	+ blink_led2
	+ iot_doorwatch
	+ iot_phtdsmeter
	+ mqtt_both
	+ mqtt_test
	+ template_c_sdk
	+ web_client
	+ web_server
	+ web_test

### STM32
- No Arduino source-code
- Only Eagle or KiCAD as PCB design
- Only C, CPP, or Makefile as sources
- Non RTOS must in a dedicated folder
- Only sources without library packages

#### List Examples
- f103rb_powermeter
- f103rb_joulemeter
- f103rb_powerlogger
- f103c8_fallsensor
- lib_alphalcd
- lib_wakeup