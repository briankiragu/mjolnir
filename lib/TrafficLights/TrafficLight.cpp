#include <Arduino.h>
#include <TrafficLight.h>

// Constructor
TrafficLight::TrafficLight(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN)
{
    redPin = RED_PIN;
    greenPin = GREEN_PIN;
    bluePin = BLUE_PIN;
}

// Getters
TrafficStatuses TrafficLight::getStatus()
{
    return status;
}

uint16_t TrafficLight::getDuration()
{
    return duration;
}

// Setters
void TrafficLight::setStatus(TrafficStatuses s)
{
    status = s;
}

void TrafficLight::setDuration(uint16_t d)
{
    duration = d;
}

/// @brief Initialise pins
void TrafficLight::setup()
{
    // Built-in LED pin.
    pinMode(LED_BUILTIN, OUTPUT);

    // Traffic lights pins.
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    // Delay for pins to set.
    delay(10);
}

void TrafficLight::turnColour(TrafficStatuses status)
{
    switch (status)
    {
    case RED:
        turnRed();
        break;

    case AMBER:
        turnAmber();
        break;

    case GREEN:
        turnGreen();
        break;

    default:
        break;
    }
}

void TrafficLight::turnRed()
{
    analogWrite(redPin, 184);
    analogWrite(greenPin, 27);
    analogWrite(bluePin, 14);
}

void TrafficLight::turnAmber()
{
    analogWrite(redPin, 247);
    analogWrite(greenPin, 181);
    analogWrite(bluePin, 0);
}

void TrafficLight::turnGreen()
{
    analogWrite(redPin, 84);
    analogWrite(greenPin, 156);
    analogWrite(bluePin, 48);
}
