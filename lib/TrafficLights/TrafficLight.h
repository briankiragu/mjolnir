#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

enum TrafficStatuses
{
    RED,
    AMBER,
    GREEN
};

class TrafficLight
{
private:
    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;

    TrafficStatuses status;
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
    TrafficStatuses getStatus();
    uint16_t getDuration();

    // Setters.
    void setStatus(TrafficStatuses s);
    void setDuration(uint16_t d);

    // Initialise pins on microcontroller.
    void setup();

    // Update the colour and duration.
    void updateColourAndDuration(TrafficStatuses status, uint16_t duration);
};

#endif
