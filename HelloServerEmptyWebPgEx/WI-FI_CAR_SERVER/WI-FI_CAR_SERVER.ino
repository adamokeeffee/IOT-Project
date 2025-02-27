
//// This code is derived from the HelloServer Example 
// in the (ESP32) WebServer library .
//
// It hosts a webpage which has one temperature reading to display.
// The webpage is always the same apart from the reading which would change.
// The getTemp() function simulates getting a temperature reading.
// homePage.h contains 2 constant string literals which is the two parts of the
// webpage that never change.
// handleRoot() builds up the webpage by adding as a C++ String:
// homePagePart1 + getTemp() +homePagePart2 
// It then serves the webpage with the command:  
// server.send(200, "text/html", message);
// Note the text is served as html.
//
// Replace the code in the homepage.h file with your own website HTML code.
// 
// This example requires only an ESP32 and download cable. No other hardware is reuired.
// A wifi SSID and password is required.

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"

const char* ssid = "";
const char* password = "";

WebServer server(80);

#define M1 27
#define E1 14
#define M2 33
#define E2 32

#define PWM_FREQ       5000
#define PWM_RES        8
#define PWM_CHANNEL_E1 0
#define PWM_CHANNEL_E2 1

void stopMotors(){
   digitalWrite(M1, LOW);
   digitalWrite(M2, LOW);
   ledcWrite(PWM_CHANNEL_E1, 0);
   ledcWrite(PWM_CHANNEL_E2, 0);
}

void controlMotor1(int speed, bool forward) {
    digitalWrite(M1, forward ? HIGH : LOW);
    ledcWrite(PWM_CHANNEL_E1, speed);
}

void controlMotor2(int speed, bool forward) {  
    digitalWrite(M2, forward ? HIGH : LOW);  
    ledcWrite(PWM_CHANNEL_E2, speed);  
}

void moveForward() {
    controlMotor1(255, true);  
    controlMotor2(255, true); 
    server.send(200, "text/plain", "Moving Forward");
}
 
void moveBackward() {
    controlMotor1(255, false);
    controlMotor2(255, false);
    server.send(200, "text/plain", "Moving Backward");
}
 
void turnLeft() {
    controlMotor1(255, false); 
    controlMotor2(255, true);  
    server.send(200, "text/plain", "Turning Left");
}
 
void turnRight() {// M
    controlMotor1(255, true);  
    controlMotor2(255, false);  
    server.send(200, "text/plain", "Turning Right");
}

String getTemp() {
  return "25.4";
}

void handleRoot() {
  String message = homePagePart1 + getTemp() + homePagePart2;
  server.send(200, "text/html", message);
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  ledcSetup(PWM_CHANNEL_E1, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_CHANNEL_E2, PWM_FREQ, PWM_RES);
  ledcAttachPin(E1, PWM_CHANNEL_E1);
  ledcAttachPin(E2, PWM_CHANNEL_E2);

  stopMotors();

  server.on("/", []() { server.send(200, "text/html", homePagePart);});
  server.on("/forward", moveForward);
  server.on("/backward", moveBackward);
  server.on("/left", turnLeft);
  server.on("/right", turnRight);
  server.on("/stop", stopMotors);


  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
