#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <TrafficLight.h>

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
    String getDeviceId();
    MqttClient *getMqttClient();
    String getMqttInboundTopic();
    String getMqttOutboundTopic();

    // Setters.
    void setDeviceId(String id);
    void setMqttClient(MqttClient *client);
    void setMqttInboundTopic(String t);
    void setMqttOutboundTopic(String t);

    // Setup network and MQTT access.
    void setupNetworkAccess(String ssid, String password);
    void setupMQTT(const String mqttBroker, const uint mqttPort);

    // Receive data over MQTT.
    TrafficPayload receiveMQTTData(int messageSize);

    // Send data over MQTT.
    void sendTrafficState(TrafficState state);
};

#endif
