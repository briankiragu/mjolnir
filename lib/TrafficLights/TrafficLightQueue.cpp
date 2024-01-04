#include <Arduino.h>
#include <TrafficLightQueue.h>

// Constructor.
TrafficLightQueue::TrafficLightQueue() {}

// Getters.
int TrafficLightQueue::getSize()
{
    return size;
}

// Setters.
int TrafficLightQueue::setSize(uint s)
{
    size = s;
}

// Add an item to the linked list.
void TrafficLightQueue::append(TrafficState state) {}

// Remove the first item of the linked list.
void TrafficLightQueue::shift() {}
