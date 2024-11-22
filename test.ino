#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Motor control pins
#define IN1 D1  
#define IN2 D2 
#define IN3 D3 
#define IN4 D4  

ESP8266WebServer server(80);

const char* ssid = "CarControl";
const char* password = "12345678";

int speedForward = 255;
int speedTurn = 190;
int speedturn = 100;
int speedQuickTurn = 255;
int speedLevel = 10;  // Default to max speed (100%)

void setup() {
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
  stopCar();

  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/normalLeft", handleNormalLeft);
  server.on("/normalRight", handleNormalRight);
  server.on("/quickLeft", handleQuickLeft);
  server.on("/quickRight", handleQuickRight);
  server.on("/rightForward", handleRightForward);
  server.on("/leftForward", handleLeftForward);
  server.on("/rightBackward", handleRightBackward);
  server.on("/leftBackward", handleLeftBackward);
  server.on("/stop", handleStop);
  server.on("/dance", handleDance);
  server.on("/setSpeed", handleSetSpeed); 
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html>\
                  <head>\
                    <title>WiFi Car Control</title>\
                    <style>\
                      body { font-family: Arial, sans-serif; text-align: center; background-color: #f2f2f2; }\
                      h1 { color: #333; }\
                      p { font-size: 18px; color: #333; }\
                      input[type='range'] { width: 80%; margin: 20px 0; }\
                    </style>\
                    <script>\
                      var keysPressed = {};\
                      document.addEventListener('keydown', function(event) {\
                        if (!keysPressed[event.key]) {\
                          keysPressed[event.key] = true;\
                          checkKeys();\
                        }\
                      });\
                      document.addEventListener('keyup', function(event) {\
                        keysPressed[event.key] = false;\
                        checkKeys();\
                      });\
                      function checkKeys() {\
                        if (keysPressed['w']) {\
                          sendCommand('/forward');\
                        } else if (keysPressed['s']) {\
                          sendCommand('/backward');\
                        } else if (keysPressed['a']) {\
                          sendCommand('/normalLeft');\
                        } else if (keysPressed['d']) {\
                          sendCommand('/normalRight');\
                        } else if (keysPressed['q']) {\
                          sendCommand('/quickLeft');\
                        } else if (keysPressed['e']) {\
                          sendCommand('/quickRight');\
                        } else if (keysPressed['u'] || (keysPressed['w'] && keysPressed['d'])) {\
                          sendCommand('/rightForward');\
                        } else if (keysPressed['y'] || (keysPressed['w'] && keysPressed['a'])) {\
                          sendCommand('/leftForward');\
                        } else if (keysPressed['j'] || (keysPressed['s'] && keysPressed['a'])) {\
                          sendCommand('/rightBackward');\
                        } else if (keysPressed['h'] || (keysPressed['s'] && keysPressed['d'])) {\
                          sendCommand('/leftBackward');\
                        } else if (keysPressed['x']) {\
                          sendCommand('/stop');\
                        } else if (keysPressed['r']) {\
                          sendCommand('/dance');\
                        } else {\
                          stopCar();\
                        }\
                      }\
                      function sendCommand(command) {\
                        var xhttp = new XMLHttpRequest();\
                        xhttp.open('GET', command, true);\
                        xhttp.send();\
                      }\
                      function stopCar() {\
                        var xhttp = new XMLHttpRequest();\
                        xhttp.open('GET', '/stop', true);\
                        xhttp.send();\
                      }\
                      function updateSpeedLevel() {\
                        var slider = document.getElementById('speedSlider');\
                        var level = Math.round((slider.value / 100) * 9) + 1;\
                        sendCommand('/setSpeed?level=' + level);\
                      }\
                    </script>\
                  </head>\
                  <body>\
                    <h1>Car Control Interface</h1>\
                    <p>Use keys: W (Forward), S (Backward), A (Left), D (Right), Q (Quick Left), E (Quick Right), U (Right Forward), Y (Left Forward), J (Right Backward), H (Left Backward), X (Stop), R (Dance Mode)</p>\
                    <p>Speed Control: Use the slider below to set speed from 10% to 100%</p>\
                    <input type='range' id='speedSlider' min='0' max='100' step='1' oninput='updateSpeedLevel()'>\
                  </body>\
                  </html>";
  server.send(200, "text/html", html);
}

void handleSetSpeed() {
  if (server.hasArg("level")) {
    int level = server.arg("level").toInt();
    if (level >= 1 && level <= 10) {
      speedLevel = level;
      speedForward = (255 * speedLevel) / 10;
      speedTurn = (190 * speedLevel) / 10;
      speedturn = (100 * speedLevel) / 10;
      speedQuickTurn = (255 * speedLevel) / 10;
    }
  }
  server.send(200);
}

void handleForward() {
  analogWrite(IN1, speedForward);
  analogWrite(IN2, 0);
  analogWrite(IN3, speedForward);
  analogWrite(IN4, 0);
  server.send(200);
}

void handleBackward() {
  analogWrite(IN1, 0);
  analogWrite(IN2, speedForward);
  analogWrite(IN3, 0);
  analogWrite(IN4, speedForward);
  server.send(200);
}

void handleNormalLeft() {
  analogWrite(IN1, speedTurn);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
  server.send(200);
}

void handleNormalRight() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, speedTurn);
  analogWrite(IN4, 0);
  server.send(200);
}

void handleQuickLeft() {
  analogWrite(IN1, speedQuickTurn);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, speedQuickTurn);
  server.send(200);
}

void handleQuickRight() {
  analogWrite(IN1, 0);
  analogWrite(IN2, speedQuickTurn);
  analogWrite(IN3, speedQuickTurn);
  analogWrite(IN4, 0);
  server.send(200);
}

void handleRightForward() {
  analogWrite(IN1, speedturn);
  analogWrite(IN2, 0);
  analogWrite(IN3, speedForward);
  analogWrite(IN4, 0);
  server.send(200);
}

void handleLeftForward() {
  analogWrite(IN1, speedForward);
  analogWrite(IN2, 0);
  analogWrite(IN3, speedturn);
  analogWrite(IN4, 0);
  server.send(200);
}

void handleRightBackward() {
  analogWrite(IN1, 0);
  analogWrite(IN2, speedturn);
  analogWrite(IN3, 0);
  analogWrite(IN4, speedForward);
  server.send(200);
}

void handleLeftBackward() {
  analogWrite(IN1, 0);
  analogWrite(IN2, speedForward);
  analogWrite(IN3, 0);
  analogWrite(IN4, speedturn);
  server.send(200);
}

void handleStop() {
  stopCar();
  server.send(200);
}

void handleDance() {  
  for (int i = 0; i < 3; i++) {
    handleForward();
    delay(300);
    handleBackward();
    delay(300);
    handleQuickLeft();
    delay(300);
    handleQuickRight();
    delay(300);
  }
  stopCar();
  server.send(200);
}

void stopCar() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}
