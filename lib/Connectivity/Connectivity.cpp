#include <ArduinoMqttClient.h>
#include <WiFi.h>

void setupNetworkAccess(String ssid, String password)
{
    // Setup complete text.
    Serial.println("Mjolnir starting...");
    Serial.println();

    Serial.print("Mjolnir connecting to: ");
    Serial.print(ssid);
    Serial.println();
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.println("Wi-Fi connected.");
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.println();
}

void setupMQTT(
    MqttClient *mqttClient,
    String deviceId,
    String mqttUsername,
    String mqttPassword,
    String mqttBroker,
    uint16_t mqttPort,
    String inboundTopic)
{
    // Each client must have a unique client ID
    mqttClient->setId(deviceId);

    // You can provide a username and password for authentication
    mqttClient->setUsernamePassword(mqttUsername, mqttPassword);

    Serial.println(
        "Device ID '" + deviceId +
        "' is attempting to connect to the MQTT broker '" + mqttBroker +
        "' on port '" + mqttPort + "'");

    if (!mqttClient->connect(mqttBroker.c_str(), mqttPort))
    {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient->connectError());

        while (1)
            ;
    }

    Serial.println(
        "Device ID '" + deviceId +
        "' is successfully connected to the MQTT broker!");
    Serial.println();

    Serial.println(
        "Device ID '" + deviceId +
        "' is subscribing to topic '" + inboundTopic + "'");
    Serial.println();

    // Subscribe to the inbound topic to receive updates.
    mqttClient->subscribe(inboundTopic);
}

void sendMessage(MqttClient *mqttClient, String outboundTopic, String message)
{
    mqttClient->beginMessage(outboundTopic);
    mqttClient->print(message);
    mqttClient->endMessage();
}

void receiveMessage(MqttClient *mqttClient, int messageSize)
{
    // We received a message, print out the topic and contents
    Serial.println("Received a message with topic '");
    Serial.print(mqttClient->messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttClient->available())
    {
        Serial.print((char)mqttClient->read());
    }
    Serial.println();
}
