#include <ArduinoMqttClient.h>
#include <WiFi.h>

extern void setupNetworkAccess(String ssid, String password);

extern void setupMQTT(
    MqttClient *mqttClient,
    String broker,
    uint16_t port,
    String deviceId,
    String topic);

extern void sendMessage(MqttClient *mqttClient, String topic, String message);
