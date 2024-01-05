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

void TrafficLight::loadTraffic(TrafficPayload payload, uint size)
{
    // Check if the incoming payload is newer.
    bool isNewer = payload.timestamp > timestamp;

    // Check if the incoming payload is of a higher priority.
    bool isUrgent = payload.priority > priority;

    // If the payload is not newer, return.
    if (!isNewer)
    {
        return;
    }

    // If the element is urgent, clear the list.
    if (isUrgent)
    {
        queue.clear();
    }

    // Update the traffic data.
    timestamp = payload.timestamp;
    priority = payload.priority;
    queue.append(payload.queue, size);
}

void TrafficLight::updateTraffic(TrafficState state)
{
    // Change the color depending on the colour.
    switch (state.colour)
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
    delay(state.duration);
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
