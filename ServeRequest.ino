
void serveRequest(){
  String message = "";

  if (server.arg("volume")== ""){     //Parameter not found
    message = "Volume argument not found";

  } else { //Parameter found
    double targetPercent = (double) server.arg("volume").toInt() / 100;
    double rotationAngle = rotateToPercent(targetPercent);
    
    message = "Volume set to: ";
    message += server.arg(targetPercent);
    message += " Rotated motor by ";
    message += rotationAngle;
    message += " degrees.";
    publishCurrentStatusToMQTT();

  }
  server.send(200, "text/plain", message);
}
