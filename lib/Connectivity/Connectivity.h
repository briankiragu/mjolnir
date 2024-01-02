extern void setupNetworkAccess(String ssid, String password);

extern void setupMQTT(
    MqttClient *mqttClient,
    String deviceId,
    String mqttUsername,
    String mqttPassword,
    String mqttBroker,
    uint16_t mqttPort,
    String inboundTopic);

extern void sendStatus(
    MqttClient *mqttClient,
    String outboundTopic,
    TrafficStatuses status);

extern void receiveMessage(MqttClient *mqttClient, int messageSize);
