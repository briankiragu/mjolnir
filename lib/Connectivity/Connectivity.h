#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

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
    void setupMQTT(const String mqttBroker, const uint16_t mqttPort);

    // Send data over MQTT.
    void sendMQTTPayload(TrafficStatuses status, uint16_t duration);

    // Receive data over MQTT.
    JSONVar receiveMQTTPayload(int messageSize);
};

#endif
