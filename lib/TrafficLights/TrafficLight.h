#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <TrafficStateQueue.h>

enum TrafficPriorities
{
    EMERGENCY,
    MAJOR,
    NORMAL,
    MINOR
};

struct TrafficPayload
{
    TrafficPriorities priority;
    uint timestamp;
    TrafficState *queue;
};

class TrafficLight
{
private:
    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;

    uint timestamp;
    TrafficPriorities priority;

    void turnRed();
    void turnAmber();
    void turnGreen();

public:
    TrafficStateQueue queue;

    // Constructor.
    TrafficLight(
        const uint8_t RED_PIN,
        const uint8_t GREEN_PIN,
        const uint8_t BLUE_PIN);

    // Initialise pins on microcontroller.
    void setup();

    // Load the traffic payload.
    void loadTraffic(TrafficPayload payload, uint size);

    // Update the colour and duration.
    void updateTraffic(TrafficState state);
};

#endif
