#include <WiFi.h>

#include <Arduino_JSON.h>
#include <ArduinoMqttClient.h>

#include <TrafficLight.h>

void setupNetworkAccess(String ssid, String password)
{
    Serial.print("Mjolnir connecting to SSID '" + ssid + "'");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.println("Wi-Fi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
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

    // Provide the username and password for authentication
    // mqttClient->setUsernamePassword(mqttUsername, mqttPassword);

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

    Serial.println(
        "Device ID '" + deviceId +
        "' is subscribing to topic '" + inboundTopic + "'");

    // Subscribe to the inbound topic to receive updates.
    mqttClient->subscribe(inboundTopic);
}

void sendPayload(
    MqttClient *mqttClient,
    String outboundTopic,
    TrafficStatuses status,
    uint16_t duration)
{
    // Build the JSON object.
    JSONVar payload;
    payload["status"] = status;
    payload["duration"] = duration;

    mqttClient->beginMessage(outboundTopic);
    mqttClient->print(JSON.stringify(payload));
    mqttClient->endMessage();
}

JSONVar receivePayload(MqttClient *mqttClient, int messageSize)
{
    // Variable to store the incoming message.
    String payload;

    // We received a message, print out the topic and contents
    Serial.println("Received a message with topic '");
    Serial.print(mqttClient->messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to get the contents
    while (mqttClient->available())
    {
        payload += (char)mqttClient->read();
    }

    // Log the incoming payload.
    Serial.println("The payload is " + payload);

    // Return the contents.
    return JSON.parse(payload);
}
