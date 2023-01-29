# LEDoN
Mobile control of RGB LED lights using a Bluetooth connection to the ESP32.

The project is designed to use two ESP8266 modules controlling RGB LEDs via D2 digital output and one ESP32 module communicating with them via ESP-NOW and the mobile app via Bluetooth.

You can edit the "ESP32/main.ino" code to increase the number of receiving devices (ESP8266) by adding their MAC addresses (broadcastAddress) to the code. You need to add their peer register in the "void setup()" method to handle ESP_NOW communication.

There are a few files in the ESP8266 folder: "secondary.ino" - the main code of the receiving device, which also contains references to header files; header files (.h) - contains LED animation functions that I found on the web and recreated for this application;

The color space used is HSV because of the ease of controlling color, saturation and brightness in animations, as well as separate values.

## Arduino IDE preferences:
In the board manager I recommend to install "esp32" from Espressif Systems in the version 1.0.6. I also recommend to install "esp8266" from ESP8266 Community in version 2.7.0. These versions are stable and work perfectly with this project. Recent versions have caused some connectivity and operation problems.

If you can't find the boards in the manager, try adding these URLs to your Arduino preferences:
https://dl.espressif.com/dl/package_esp32_index.json 
http://arduino.esp8266.com/stable/package_esp8266com_index.json

## HOW TO MANAGE THESE FILES:

1. You need to get MAC addresses from your ESP8266 devices and put them into "main.ino".
2. Then send "main.ino" file to your ESP32 device.
3. Next step is to send "secondary.ino" file to your ESP8266 devices.
4. Install "LEDoN.apk" on your Android phone, turn on bluetooth and try to connect to ESP32 device (device name can be edited in "main.ino").
5. Run the LEDoN application, connect to the ESP32 device and have fun :)

### In the LEDoN app, you can:
- Turn on and off LED strips
- Control hue, saturation and brightness
- Choose number of controlled LED modules in your LED strip
- Choose one of many animations.
- In each animation you can control the brightness.
- In some animations you can control their hue and saturation.
- You can modify the apk by importing "LEDoN.aia" into Kodular.io.

You can modify the apk by importing "LEDoN.aia" into Kodular.io.
