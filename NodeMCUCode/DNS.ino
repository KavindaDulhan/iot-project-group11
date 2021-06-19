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

// Activate the DNS server
void initDNS()
{
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

  // Start DNS server for a specific domain name
  dnsServer.start(DNS_PORT, "esp8266.local", WiFi.softAPIP());
}
