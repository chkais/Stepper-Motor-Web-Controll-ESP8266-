

void serveRequest(){
  String message = "";

  if (server.arg("volume")== ""){     //Parameter not found
    message = "Volume Argument not found";

  } else { //Parameter found
    double targetPercent = (double) server.arg("volume").toInt() / 100;
    Serial.print("targetPercent: ");
    Serial.println(targetPercent);
    double rotationAngle = (targetPercent * MAX_ANGLE) - CURRENT_ANGLE;
    CURRENT_ANGLE = CURRENT_ANGLE + rotationAngle;
    
    Serial.print("Rotation Angle: ");
    Serial.println(rotationAngle);
    Serial.print("Current Angle: ");
    Serial.println(CURRENT_ANGLE);

    message = "Volume Argument = ";
    message += server.arg(targetPercent);

    rotate(rotationAngle);
    writeCurrentAngleToFile();
  }
  server.send(200, "text/plain", message);
}

