
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>



String CURRENT_ANGLE_PATH = "/CURRENT_ANGLE.txt";
int CURRENT_ANGLE = 0;
int MAX_ANGLE = 360;

ESP8266WebServer server(80);

void setup() {
  //ESP8266 
  Serial.begin(115200);
  Serial.println("--------- 1: Initialize WiFi --------------------------------------");
  initWifi();
  Serial.println("--------- 1: Finished - WiFi initialized --------------------------");
  
  Serial.println("--------- 2: Initialize Stepper Motor -----------------------------");
  initStepper();
  Serial.println("--------- 2: Finished - Stepper Motor initialized -----------------");

  Serial.println("--------- 3: Initialize FileSystem --------------------------------");
  initializeFileSystem();
  Serial.println("--------- 3: Finished - FileSystem initialized --------------------");

  // Initialize HTTP Server
  Serial.println("--------- 4: Initialize HTTP Server -------------------------------");
  server.on("/", serveRequest);
  server.begin();
  Serial.println("--------- 4: Finished - HTTP Server initialized -------------------");
  Serial.println("");
  Serial.println("Waiting for requests....");

}

void loop() {
  server.handleClient();
}

void initializeFileSystem(){
  if(SPIFFS.begin())
  {
    if (SPIFFS.exists(CURRENT_ANGLE_PATH)){
      setCurrentAngleFromFile();
    } else {
      writeCurrentAngleToFile();
    }
  }
  else
  {
    Serial.println("SPIFFS Initialization...failed");
  }  
}


void setCurrentAngleFromFile(){
  File f = SPIFFS.open(CURRENT_ANGLE_PATH, "r");
  if (!f) {
     Serial.println("file open failed");
  }
  //Lets read the first line from the file
  String line = f.readStringUntil('\n');
  CURRENT_ANGLE = line.toInt();
  f.close();
}

void writeCurrentAngleToFile(){
  File f = SPIFFS.open(CURRENT_ANGLE_PATH, "w");
  if (!f) {
     Serial.println("file open failed");
  }
  f.println(CURRENT_ANGLE);
  f.close();
}

