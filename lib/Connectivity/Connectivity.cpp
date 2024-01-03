#include <WiFi.h>

#include <Arduino_JSON.h>
#include <ArduinoMqttClient.h>

#include <TrafficLight.h>
#include <Connectivity.h>

Connectivity::Connectivity(
    MqttClient *mqttClient,
    const String id,
    const String mqttInboundTopic,
    const String mqttOutboundTopic,
    const String mqttUsername,
    const String mqttPassword)
{
    setMqttClient(mqttClient);
    setDeviceId(id);
    setMqttInboundTopic(mqttInboundTopic);
    setMqttOutboundTopic(mqttOutboundTopic);

    // Each client must have a unique client ID.
    getMqttClient()->setId(getDeviceId());

    // Provide the username and password for authentication.
    getMqttClient()->setUsernamePassword(mqttUsername, mqttPassword);
}

MqttClient *Connectivity::getMqttClient()
{
    return mqttClient;
}

String Connectivity::getDeviceId()
{
    return deviceId;
}

String Connectivity::getMqttInboundTopic()
{
    return mqttInboundTopic;
}

String Connectivity::getMqttOutboundTopic()
{
    return mqttOutboundTopic;
}

void Connectivity::setMqttClient(MqttClient *client)
{
    mqttClient = client;
}

void Connectivity::setDeviceId(String id)
{
    deviceId = id;
}

void Connectivity::setMqttInboundTopic(String t)
{
    mqttInboundTopic = t;
}

void Connectivity::setMqttOutboundTopic(String t)
{
    mqttOutboundTopic = t;
}

void Connectivity::setupNetworkAccess(const String ssid, const String password)
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

void Connectivity::setupMQTT(const String mqttBroker, const uint16_t mqttPort)
{
    Serial.println(
        "Device ID '" + getDeviceId() +
        "' is attempting to connect to the MQTT broker '" + mqttBroker +
        "' on port '" + mqttPort + "'");

    if (!getMqttClient()->connect(mqttBroker.c_str(), mqttPort))
    {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(getMqttClient()->connectError());

        while (1)
            ;
    }

    Serial.println(
        "Device ID '" + getDeviceId() +
        "' is successfully connected to the MQTT broker!");

    Serial.println(
        "Device ID '" + getDeviceId() +
        "' is subscribing to topic '" + getMqttInboundTopic() + "'");

    // Subscribe to the inbound topic to receive updates.
    getMqttClient()->subscribe(getMqttInboundTopic());
}

void Connectivity::sendMQTTPayload(TrafficStatuses status, uint16_t duration)
{
    // Build the JSON object.
    JSONVar payload;
    payload["status"] = status;
    payload["duration"] = duration;

    getMqttClient()->beginMessage(getMqttOutboundTopic());
    getMqttClient()->print(JSON.stringify(payload));
    getMqttClient()->endMessage();
}

JSONVar Connectivity::receiveMQTTPayload(int messageSize)
{
    // Variable to store the incoming message.
    String payload;

    // We received a message, print out the topic and contents
    Serial.println("Received a message with topic '");
    Serial.print(getMqttClient()->messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to get the contents
    while (getMqttClient()->available())
    {
        payload += (char)getMqttClient()->read();
    }

    // Log the incoming payload.
    Serial.println("The payload is " + payload);

    // Return the contents.
    return JSON.parse(payload);
}
