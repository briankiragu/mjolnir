#include <Arduino.h>
#include <TrafficLights.h>
#include <WiFi.h>

const uint8_t RED_PIN = 15;
const uint8_t GREEN_PIN = 2;
const uint8_t BLUE_PIN = 4;

const char *ssid = "Faiba";
const char *password = "kariuki@2022";

WiFiServer server(80);

void setup()
{
    // Serial output.
    Serial.begin(115200);

    // Built-in LED pin.
    pinMode(LED_BUILTIN, OUTPUT);

    // Traffic lights pins.
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    // Delay for pins to set.
    delay(10);

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

    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.println();
    server.begin();
}

void loop()
{
    // Turn the lights RED.
    turnRed(RED_PIN, GREEN_PIN, BLUE_PIN);
    delay(1000);

    // Turn the lights AMBER.
    turnAmber(RED_PIN, GREEN_PIN, BLUE_PIN);
    delay(1000);

    // Turn the lights AMBER.
    turnGreen(RED_PIN, GREEN_PIN, BLUE_PIN);
    delay(1000);
}
