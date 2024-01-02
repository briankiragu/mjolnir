enum TrafficStatuses
{
    RED,
    AMBER,
    GREEN
};

extern void setupTrafficLights(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN);

extern void turnRed(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN);

extern void turnAmber(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN);

extern void turnGreen(uint8_t RED_PIN, uint8_t GREEN_PIN, uint8_t BLUE_PIN);

extern void turnColour(
    uint8_t RED_PIN,
    uint8_t GREEN_PIN,
    uint8_t BLUE_PIN,
    TrafficStatuses status);
