#include <Arduino.h>

void turnRed(uint8_t RED_PIN, uint8_t BLUE_PIN, uint8_t GREEN_PIN)
{
    analogWrite(RED_PIN, 255);
    analogWrite(BLUE_PIN, 0);
    analogWrite(GREEN_PIN, 0);
}

void turnAmber(uint8_t RED_PIN, uint8_t BLUE_PIN, uint8_t GREEN_PIN)
{
    analogWrite(RED_PIN, 255);
    analogWrite(BLUE_PIN, 191);
    analogWrite(GREEN_PIN, 0);
}

void turnGreen(uint8_t RED_PIN, uint8_t BLUE_PIN, uint8_t GREEN_PIN)
{
    analogWrite(RED_PIN, 0);
    analogWrite(BLUE_PIN, 0);
    analogWrite(GREEN_PIN, 255);
}
