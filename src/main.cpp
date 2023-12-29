#include <Arduino.h>
#include <TrafficLights.h>

const uint8_t RED_PIN = 15;
const uint8_t GREEN_PIN = 2;
const uint8_t BLUE_PIN = 4;

void setup()
{
    // Built-in LED pin.
    pinMode(LED_BUILTIN, OUTPUT);

    // Traffic lights pins.
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
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
