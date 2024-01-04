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
    Node *head = nullptr;
    Node *tail = nullptr;
    uint size;

public:
    // Add an item to the linked list.
    void enqueue(TrafficState state);

    // Remove the first item of the linked list.
    void dequeue();

    // Build a linked list from a regular list.
    void fill(TrafficState *list, uint size);
};

#endif
