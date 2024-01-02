#include <Arduino_JSON.h>

extern void setupNetworkAccess(String ssid, String password);

extern void setupMQTT(
    MqttClient *mqttClient,
    String deviceId,
    String mqttUsername,
    String mqttPassword,
    String mqttBroker,
    uint16_t mqttPort,
    String inboundTopic);

extern void sendPayload(
    MqttClient *mqttClient,
    String outboundTopic,
    TrafficStatuses status,
    uint16_t duration);

extern JSONVar receivePayload(MqttClient *mqttClient, int messageSize);
