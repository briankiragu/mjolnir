#include <ArduinoMqttClient.h>
#include <WiFi.h>

extern void setupNetworkAccess(String ssid, String password);

extern void setupMQTT(
    MqttClient *mqttClient,
    String deviceId,
    String mqttUsername,
    String mqttPassword,
    String mqttBroker,
    uint16_t mqttPort,
    String inboundTopic);

extern void sendMessage(
    MqttClient *mqttClient,
    String outboundTopic,
    String message);

extern void receiveMessage(MqttClient *mqttClient, int messageSize);
