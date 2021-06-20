// Initialize the web server
void initServer()
{
  initMDNS();
  initDNS();
  routeServer();
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Web Server Started!\n");
}

// Define server routing
void routeServer()
{
  server.on("/", HTTP_GET, []()
            { server.send(200, F("text/html"),
                          F("Welcome to the REST Web Server")); });
  server.on(F("/helloWorld"), HTTP_GET, getAQI);
}

// Web client handling
void handleServerClients()
{
  MDNS.update();
  dnsServer.processNextRequest();
  server.handleClient();
}

// Serving AQI
void getAQI()
{
  setCrossOrigin();
  AQIMsg.toCharArray(_server_buf, BUF_SIZE);
  server.send(200, "text/json", _server_buf);
  Serial.print("Web Server Sent Message : ");
  Serial.println(AQIMsg);
}

// CORS
void setCrossOrigin()
{
  server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
  server.sendHeader(F("Access-Control-Max-Age"), F("600"));
  server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
  server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};

// Not found response
void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
