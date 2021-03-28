# Stepper-Motor-Web-Controll-ESP8266
This project allows a ULN2003 Stepper Motor to be controlled via web request.

## Setup / Before you start
 1. Download the Arduino IDE
 2. Import all files as an arduino sketchbook
 3. Adapt the WiFi settings in the WiFi Tab
 4. If you want to use MQTT configure the settings in the mqtt-tab
 5. Configure the maximum angle the motor should rotate. This can be any digit greater zero (>0 :wink:). It depends on your motor setup.
 6. Change the parameter name in the ServeRequest-Tab to one you like. For me it was 'volume' because I control the volume wheel of an amplifier
 7. Change the PIN-configuration in 'StepperMotorControl'-Tab depending on your hardware setup. Since I am working with a NodeMCU board I choosed the following setup: 
 ```c++
#define IN1 14 // GPIO 14 / D5
#define IN2 12 // GPIO 12 / D6
#define IN3 13 // GPIO 13 / D7
#define IN4 15 // GPIO 15 / D8
 ```

## How to use
### HTTP
Just open a new tab in your favorite browser and enter the following url:
http://\<IP-of-your-esp9266\>/?volume=80

This will set the rotation angle to 80% of the configured maximum angle.

### MQTT
<TBD>

### MQTT Home-Assistant
Check copy the content of the 'ha-config.yml'-file to your home assistant configuration (configuration.yml). Then you will have an entity to use this control via your ha userinterface

## Additional Comments
  I used [HA-Bridge](https://github.com/bwssytems/ha-bridge) to control my volume via Amazon Alexa. For this I had to make the IP for the ESP8266 static (I did it on the router, but do as you prefer). For more information on how to configure this, just go to the linked github project. The documentation is very comprehensive.

## Possible improvements
  * You could setup a reset button and some mechanism to determine the maximum rotation angle
  * Response as JSON
  * ...
