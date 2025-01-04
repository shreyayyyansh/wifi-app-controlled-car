# wifi-app-controlled-car
DIY IoT car that runs through wifi and a mobile app and website.

EQUIPMENTS REQUIRED:
1. ESP8266 nodeMCU board
2. L298N motor driver
3. Breadboard
4. Motors
5. 12v D.C. power supply
6. Wheels
7. Jumperwires both M2M & M2F
8. USB cable
9. A phone/laptop to work on

Development of ESP board is not enabled by default, to install the ESP8266 board in your Arduino IDE, follow these next instructions:

1. Open the preferences window from the Arduino IDE. Go to File>Preferences
2. Enter http://arduino.esp8266.com/stable/package_esp8266com_in
dex.json into Additional Board Manager URLs field and press the 
“OK” button.
3. Go to Tools>Board>Boards Manager
4. Scroll down, select the ESP8266 board menu and Install “esp8266 by 
ESP8266 Community”
5. Go to Tools>Board>NodeMCU 1.0 (ESP-12E Module)
6. Finally, re-open your Arduino IDE to ensure that it launches with the 
new boards installed.

Now, copy the code file and paste it on Arduino IDE.

Transfer it to the board and install the given apk application on your mobile phone.

Make the connections between all the components and connect it to power supply. (Refer to the attached pin diagram) 

https://app.cirkitdesigner.com/project/8e7db4f4-b755-4c90-a2d8-1b4cf69ea520 (link to the editable circuit)

There are 2 ways to control the car:
1. Controlling through an Android phone:

(i) Install the .apk file on your phone.

(ii) Now connect your phone to car's wifi network.

(iii) Open the app and you're good to go.

2. Controlling through your laptop:

(i) Connect your laptop to car's wifi network.

(ii) Go to https://192.168.4.1/ on any web browser of your choice.

Enjoy!
