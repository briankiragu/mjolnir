#include <Arduino.h>

#include <Connectivity.h>
#include <TrafficLights.h>

const uint8_t RED_PIN = 15;
const uint8_t GREEN_PIN = 2;
const uint8_t BLUE_PIN = 4;

const char *ssid = "Faiba";
const char *password = "kariuki@2022";

const char *uuid = "018cb5ee-bce0-79fc-b2d6-bc97955d28f1";

void setup()
{
    // Serial output.
    Serial.begin(115200);

    // Setup the traffic light LED.
    setupTrafficLights(RED_PIN, GREEN_PIN, BLUE_PIN);

    // Setup the Wi-Fi connection.
    setupConnectivity(ssid, password);
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
