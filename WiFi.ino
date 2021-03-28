const char* ssid = SECRET_WIFI;
const char* password = SECRET_WIFI_PASSWORD;
void initWifi()
{

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("  - Trying to connect to WiFi '");
  Serial.print(ssid);
  Serial.print("':\n  ");

  // Wait for connection
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (counter == 120 ) {
      Serial.print(" failed\n  ");
      ESP.deepSleep(10e6); // 10e6 is 10 seconds
    }
    delay(100);
    Serial.print(".");
    counter += 1;
  }
  Serial.println(" connected!");
  Serial.print("  - IP address  : ");
  Serial.println(WiFi.localIP());
}
