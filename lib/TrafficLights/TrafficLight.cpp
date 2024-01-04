#include <Arduino.h>
#include <TrafficLight.h>

// Constructor
TrafficLight::TrafficLight(
    const uint8_t RED_PIN,
    const uint8_t GREEN_PIN,
    const uint8_t BLUE_PIN)
{
    redPin = RED_PIN;
    greenPin = GREEN_PIN;
    bluePin = BLUE_PIN;
}

// Getters
TrafficState TrafficLight::getState()
{
    return state;
}

// Setters
void TrafficLight::setState(TrafficState s)
{
    state = s;
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

void TrafficLight::enqueueTraffic(TrafficPayload payload, uint queueSize)
{
    // Check if the new payload is newer.
    bool isNewer = payload.timestamp > timestamp;

    // Check if the new payload is a higher priority.
    bool isUrgent = payload.priority > priority;

    // If the element is newer and urgent, replace the list.
    if (isNewer && isUrgent)
    {
        //
    }

    // If the element is newer but not urgent, append it to the list.
    if (isNewer && !isUrgent)
    {
        //
    }
}

void TrafficLight::updateTraffic()
{
    // Change the color depending on the colour.
    switch (getState().colour)
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

    // Maintain the colour for the specified duration.
    delay(getState().duration);
}
