# LEDoN
 Mobile control the RGB LED lights by using a bluetooth connection to the ESP32.

The project is designed to use two ESP8266 modules controlling RGB leds via D2 digital output and an ESP32 module communicating with them via ESP-NOW and the mobile app via Bluetooth.

You can edit "ESP32/main.ino" code to increase the number of receiving devices (ESP8266) by adding their MAC addresses (broadcastAddress) into code.
You need to add their peer register in the "void setup()" function to handle ESP_NOW communication.

In "ESP8266" folder there are a few files: 
"secondary.ino" - the main code of the receiving device, which also includes references to header files ; 
header files (.h) - contains led animation functions, which I found in the web and recreated for this application;

The color space used is HSV because of the ease of controlling colors, saturation and brightness in animations, as well as separate values.

Arduino IDE preferences:
In board manager I recommend to install "esp32" by Espressif Systems in 1.0.6 version. Also recommend to install "esp8266" by ESP8266 Comunity in 2.7.0 version. These versions are stable and works perfectly with this project. Newer versions have caused some connectivity problems.
If you can't find the boards in the manager, try pasting these URLs in the Arduino preferences:
https://dl.espressif.com/dl/package_esp32_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json

HOW TO MANAGE THESE FILES:

1. You need to get MAC adresses from your ESP8266 devices and apply them into "main.ino".
2. Then send "main.ino" file into your ESP32 device.
3. Next step is send "secondary.ino" file into your ESP8266 devices.
4. Install "LEDoN.apk" on your android phone, turn on bluetooth, and try connect with ESP32 device (name of device can be edited in the "main.ino")
5. Turn on LEDoN application, connect with ESP32 device, and have a fun :)

In the LEDoN app, you can:
- turn on and off
- controll hue, saturation and brightness
- choose ammount of controlled LED modules despite of your LED stripe
- choose one of plenty animations
- in every animation, you can control brigtness
- in some animations you can control their hue and saturation 

You can modify the apk by importing "LEDoN.aia" into Kodular.io.
