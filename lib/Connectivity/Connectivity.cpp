#include <WiFi.h>

void setupConnectivity(
    WiFiServer *server,
    const char *ssid,
    const char *password)
{
    // Setup complete text.
    Serial.println("Mjolnir starting...");
    Serial.println();

    Serial.print("Mjolnir connecting to: ");
    Serial.print(ssid);
    Serial.println();
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.println("Wi-Fi connected.");
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.println();

    server->begin();
}
