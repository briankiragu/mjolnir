#ifndef TRAFFICLIGHTQUEUE_H
#define TRAFFICLIGHTQUEUE_H

enum TrafficColours
{
    RED,
    AMBER,
    GREEN
};

struct TrafficState
{
    TrafficColours colour;
    uint duration;
};

struct Node
{
    TrafficState state;
    Node *next;
};

class TrafficLightQueue
{
private:
    Node *head;
    uint size;

public:
    // Constructor.
    TrafficLightQueue();

    // Getters.
    int getSize();

    // Setters.
    int setSize(uint s);

    // Add an item to the linked list.
    void append(TrafficState state);

    // Remove the first item of the linked list.
    void shift();
};

#endif
