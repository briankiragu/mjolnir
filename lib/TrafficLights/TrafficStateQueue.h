#ifndef TRAFFICSTATEQUEUE_H
#define TRAFFICSTATEQUEUE_H

#define MAX_STATES_COUNT 100

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

class TrafficStateQueue
{
private:
    struct Node
    {
        TrafficState state;
        Node *next;

        // Copy constructor
        Node(const TrafficState &otherState, Node *nextNode)
            : state(otherState), next(nextNode) {}

        // Assignment operator
        Node &operator=(const Node &other)
        {
            if (this != &other)
            {
                state = other.state;
                next = other.next;
            }
            return *this;
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    uint size = 0;

public:

    // Check if the queue is empty.
    bool isEmpty();

    // Get the first item in the linked list.
    TrafficState *peek();

    // Add an item to the linked list.
    void enqueue(TrafficState state);

    // Remove the first item of the linked list.
    void dequeue();

    // Add the items from a regular list onto the end.
    void append(TrafficState list[MAX_STATES_COUNT]);

    // Clear the linked list.
    void clear();

    // Method to display the linked list
    void display();

    // Destructor.
    ~TrafficStateQueue();
};

#endif
