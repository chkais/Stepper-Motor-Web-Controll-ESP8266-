const char* mqttServer = SECRET_MQTTSERVER;
const int mqttPort = 1883;
const char* mqttUser = SECRET_MQTTUSER;
const char* mqttPassword = SECRET_MQTTPWD;

int timeLast = millis() / 1000;

void setupMQTT(){
  client.setServer(mqttServer, mqttPort);
  client.setCallback(mqttCallback);

  int retryCounter = 0;
  while (!client.connected() && retryCounter < 5) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP9266_Volume_Control", mqttUser, mqttPassword )) {
      Serial.println("connected");  
    } else {
      retryCounter++;
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  client.subscribe("esp_custom/volume_control_anlage/#");
  publishCurrentStatusToMQTT();
}

void mqttLoop(){
  int timeNow = millis() / 1000;
  if (timeNow - timeLast > 60){
      publishCurrentStatusToMQTT();
      timeLast = timeNow;
  }
  client.loop();
}

void publishCurrentStatusToMQTT(){
  client.publish("esp_custom/volume_control_anlage/status", "{ status: 'ON'}");
  client.publish("esp_custom/volume_control_anlage/brightness/status", String((CURRENT_ANGLE / (double) MAX_ANGLE) * 255).c_str());
}


void mqttCallback(char* topic, byte* payload, unsigned int length) {
  // If you want to publish a message from within the message callback function, 
  // it is necessary to make a copy of the topic and payload values as the client 
  // uses the same internal buffer for inbound and outbound messages:
  byte* payloadCopy = (byte*)malloc(length);
  // Copy the payload to the new buffer
  memcpy(payloadCopy,payload,length);
  
  if (strcmp(topic,"esp_custom/volume_control_anlage/brightness/set")==0){
      int message = atoi((char*)payloadCopy);
      double volumePercent = (double)message / 255.0;
      rotateToPercent(volumePercent);
      client.publish("esp_custom/volume_control_anlage/brightness/status", String(volumePercent * 255).c_str());
  } else if (strcmp(topic,"esp_custom/volume_control_anlage/switch")==0){
      client.publish("esp_custom/volume_control_anlage/status", "ON");
  }
  // see above
  free(payloadCopy);
}
