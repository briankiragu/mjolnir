#include <Arduino.h>

void setupTrafficLights(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN)
{
    // Built-in LED pin.
    pinMode(LED_BUILTIN, OUTPUT);

    // Traffic lights pins.
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    // Delay for pins to set.
    delay(10);
}

void turnRed(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN)
{
    analogWrite(RED_PIN, 184);
    analogWrite(GREEN_PIN, 27);
    analogWrite(BLUE_PIN, 14);
}

void turnAmber(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN)
{
    analogWrite(RED_PIN, 247);
    analogWrite(GREEN_PIN, 181);
    analogWrite(BLUE_PIN, 0);
}

void turnGreen(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN)
{
    analogWrite(RED_PIN, 84);
    analogWrite(GREEN_PIN, 156);
    analogWrite(BLUE_PIN, 48);
}
