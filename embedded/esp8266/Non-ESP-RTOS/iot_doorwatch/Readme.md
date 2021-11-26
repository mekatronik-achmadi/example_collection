This contains [ESP8266EX](https://www.espressif.com/en/products/hardware/esp8266ex/overview) development as an alternative to [latest official](https://github.com/SafeVisionID/esp-latestcode) development.
This hopes can be scale-up as implementation/requirement applied.

Based on [ESP-Open-SDK](https://github.com/pfalcon/esp-open-sdk) which in turn based on Espressif's [Non-OS SDK](https://github.com/espressif/ESP8266_NONOS_SDK)

To install required SDK:
- Arch-Linux, available at [AUR](https://aur.archlinux.org/packages/esp-open-sdk-git/)
- Others, follow this [guide](https://github.com/pfalcon/esp-open-sdk/blob/master/README.md)

-----------------------------------------------------------------------

Fearture and To-Do list:
- [x] Basic LED Blink
- [x] UART Boot Info
- [x] UART Shell and Response/Callback
- [x] GPIO Interrupt (using Polling)
- [x] Basic HTTP Server
	- [x] Basic HTML Response
	- [x] Serial Out Response
	- [x] Reset Request
	- [x] R/W Integer/String in Flash
	- [x] Receive Serial Request
- [x] Wifi Station mode
	- [x] Config Password
	- [x] Config SSID
- [x] Wifi SoftAP mode
	- [x] Default IP, SSID, and Password
	- [x] Config Station SSID and Password
	- [x] Config Device ID
- [x] Switch Station and SoftAP
	- [x] WiFi Status Indicator (LED GPIO2)
	- [x] by HTTP Request
	- [x] by GPIO pin
- [ ] Sensor Interface
	- [x] Magnet Switch
	- [x] PIR (Cont-Trigger and 3v3)
	- [ ] Server Checking
	- [ ] Server Report
- [ ] Sleep and WakeUp
	- [x] by Sleep Time-Out
	- [ ] by Sensor Trigger
- [ ] Power Manager Circuit
	- [ ] Battery (LiPO)
	- [ ] Regulator (AMS1117)
- [ ] PCB
	- [x] Main
	- [ ] Battery Regulator
- [ ] Additional
	- [x] ADC Interface
	
-----------------------------------------------------------------------

IoT API:
- [x] Test:
	
	- Debug Serial Command:
	~~~
	apitest
	~~~
	
	- URL:
	~~~
	POST /sensor/test
	~~~
	
	- HEADER:
	~~~
	"Content-Type: application/json\r\n" \
    "Accept: application/json\r\n";
	~~~
	
	- BODY:
	~~~
	"{\n"\
    "\"testMessage\": \"connection\"\n" \
    "}\n";
	~~~

	- RESPONSE:
	~~~
	{
  	"message": "Connected"
	}
	~~~
	
- [ ] Create:
	
	- Debug Serial Command:
	~~~
	apicreate
	~~~
	
	- URL:
	~~~
	POST /sensor/test
	~~~
	
	- HEADER:
	~~~
	"Content-Type: application/json\r\n" \
    "Accept: application/json\r\n" \
    "x-access-token={TOKEN_STRING}\r\n" 
	~~~
	
	- BODY:
	~~~
	"{\n" \
	"\"id\": \"DEVICE_ID\",\n" \
	"\"jenis\": \"alarm\",\n" \
	"}\n";
	~~~
	
	- RESPONSE:
	~~~
	{
	"data": [],
	"_id": "SNSR0001",
	"jenis": "alarm",
	"status": "0",
	"username": "user2@gmail.com",
	"long": "3423480923.21",
	"lat": "2342830420938.22",
	"__v": 0
	}
	~~~


-----------------------------------------------------------------------

Copyright (C) Wira ST MT