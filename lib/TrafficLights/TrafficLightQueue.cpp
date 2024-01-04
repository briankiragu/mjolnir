#include <Arduino.h>
#include <TrafficLightQueue.h>

// Add an item to the linked list.
void TrafficLightQueue::enqueue(TrafficState state)
{
    // Create a new node.
    Node newNode = {state, nullptr};

    // If the head is null (this is the first element),
    // point both head and tail to it.
    if (head == nullptr)
    {
        head = &newNode;
    }
    else
    {
        *tail->next = newNode;
    }
    tail = &newNode;
    size++;
}

// Remove the first item of the linked list.
void TrafficLightQueue::dequeue()
{
    head = head->next;
    size--;
}

// Build a linked list from a regular list.
void TrafficLightQueue::fill(TrafficState *list, uint size)
{
    for (size_t i = 0; i < size; i++)
    {
        enqueue(list[i]);
    }
}
