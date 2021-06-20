// Activate mDNS to connect to the server
void initMDNS()
{
  // Local mDNS hostname
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

// Start DNS server
void initDNS()
{
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

  // DNS hostname
  Serial.print("DNS Server Deployment : ");
  Serial.println(dnsServer.start(DNS_PORT, dns_hostname, WiFi.softAPIP()) ? "Success!" : "Failed!");
  Serial.println();
}
