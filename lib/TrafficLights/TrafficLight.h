#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <TrafficLightQueue.h>

#define MAX_STATES_COUNT 100

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

    TrafficState *queue;
    uint8_t queueSize;

    TrafficState state;

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
    uint getTimestamp();
    TrafficPriorities getPriority();
    TrafficState *getQueue();
    uint getQueueSize();
    TrafficState getState();

    // Setters.
    void setTimestamp(uint t);
    void setPriority(TrafficPriorities p);
    void setQueue(TrafficState *q);
    void setQueueSize(uint s);
    void setState(TrafficState s);

    // Initialise pins on microcontroller.
    void setup();

    // Load the traffic payload.
    void enqueueTraffic(TrafficPayload paylod, uint queueSize);

    // Update the colour and duration.
    void updateTraffic();
};

#endif
