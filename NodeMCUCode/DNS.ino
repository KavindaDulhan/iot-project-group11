// Activate mDNS to connect to the server
void initMDNS()
{
  // Local DNS hostmane esp8266.local
  if (!MDNS.begin("esp8266"))
  {
    Serial.println("Error Setting up MDNS Responder!");
    while (1)
    {
      delay(1000);
    }
  }
  Serial.println("mDNS Responder Started");
}

// Activate a DNS server
// void dnsInit()
// {
//   dnsServer.setTTL(300);
//   dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

//   // start DNS server for a specific domain name
//   dnsServer.start(DNS_PORT, "www.esp8266.local", WiFi.localIP());
// }
