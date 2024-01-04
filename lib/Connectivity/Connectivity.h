#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <TrafficLight.h>

struct MQTTPayload
{
    TrafficPriorities priority;
    uint timestamp;
    TrafficState queue[MAX_STATES_COUNT];
};

class Connectivity
{
private:
    String deviceId;
    String mqttInboundTopic;
    String mqttOutboundTopic;

public:
    MqttClient *mqttClient;

    // Constructor.
    Connectivity(
        MqttClient *mqttClient,
        const String id,
        const String mqttInboundTopic,
        const String mqttOutboundTopic,
        const String mqttUsername,
        const String mqttPassword);

    // Getters.
    MqttClient *getMqttClient();
    String getDeviceId();
    String getMqttInboundTopic();
    String getMqttOutboundTopic();

    // Setters.
    void setMqttClient(MqttClient *client);
    void setDeviceId(String id);
    void setMqttInboundTopic(String t);
    void setMqttOutboundTopic(String t);

    // Setup network and MQTT access.
    void setupNetworkAccess(String ssid, String password);
    void setupMQTT(const String mqttBroker, const uint mqttPort);

    // Receive data over MQTT.
    MQTTPayload receiveMQTTData(int messageSize);

    // Send data over MQTT.
    void sendTrafficState(TrafficState state);
};

#endif
