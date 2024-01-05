#include <Arduino.h>
#include <TrafficStateQueue.h>

TrafficStateQueue::~TrafficStateQueue()
{
    clear();
}

// Check if the queue is empty.
bool TrafficStateQueue::isEmpty()
{
    return head == nullptr;
}

// Get the first item in the linked list.
TrafficState *TrafficStateQueue::peek()
{
    if (!isEmpty())
    {
        return &head->state;
    }

    // Return nullptr when the queue is empty
    return nullptr;
}

// Add an item to the linked list.
void TrafficStateQueue::enqueue(TrafficState state)
{
    // Create a new node.
    Node *newNode = new Node{state, nullptr};

    // If the head is null (this is the first element),
    // point both head and tail to it.
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        tail->next = newNode;
    }
    tail = newNode;
    size++;
}

// Remove the first item of the linked list.
void TrafficStateQueue::dequeue()
{
    Node *temp = head;
    head = head->next;
    delete temp;

    if (head == nullptr)
    {
        tail = nullptr;
    }

    size--;
}

// Add the items from a regular list onto the end.
void TrafficStateQueue::append(TrafficState *list, uint size)
{
    for (size_t i = 0; i < size; i++)
    {
        enqueue(list[i]);
    }
}

// Clear the linked list.
void TrafficStateQueue::clear()
{
    while (head != nullptr)
    {
        dequeue();
    }

    tail = nullptr;
    size = 0;
}
