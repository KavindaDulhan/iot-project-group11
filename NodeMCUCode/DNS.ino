// Activate mDNS to connect to the server
void initMDNS()
{
  // Local DNS hostname esp8266.local
  if (!MDNS.begin(mdns_hostname))
  {
    Serial.println("\nError Setting up MDNS Responder!\n");
    while (1)
    {
      delay(1000);
    }
  }
  Serial.println("\nmDNS Responder Started!\n");
}

// Activate the DNS server
void initDNS()
{
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

  // Start DNS server for a specific domain name
  Serial.print("DNS Server Deployment : ");
  Serial.println(dnsServer.start(DNS_PORT, dns_hostname, WiFi.softAPIP()) ? "Success!" : "Failed!");
  Serial.println();
}
