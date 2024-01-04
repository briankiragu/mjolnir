#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

enum TrafficPriorities
{
    EMERGENCY,
    MAJOR,
    NORMAL,
    MINOR
};

enum TrafficColours
{
    RED,
    AMBER,
    GREEN
};

struct TrafficState
{
    TrafficColours colour;
    uint16_t duration;
};

struct TrafficPayload
{
    TrafficPriorities priority;
    uint timestamp;
    TrafficState *states;
};

class TrafficLight
{
private:
    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;

    TrafficColours colour;
    uint16_t duration;

    void turnRed();
    void turnAmber();
    void turnGreen();

public:
    // Constructor.
    TrafficLight(
        const uint8_t RED_PIN,
        const uint8_t GREEN_PIN,
        const uint8_t BLUE_PIN);

    // Getters.
    TrafficColours getStatus();
    uint16_t getDuration();

    // Setters.
    void setStatus(TrafficColours s);
    void setDuration(uint16_t d);

    // Initialise pins on microcontroller.
    void setup();

    // Update the colour and duration.
    void updateColourAndDuration(TrafficColours colour, uint16_t duration);
};

#endif
