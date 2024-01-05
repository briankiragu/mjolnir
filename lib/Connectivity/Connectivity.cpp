#include <WiFi.h>

#include <ArduinoJson.h>
#include <ArduinoMqttClient.h>

#include <Connectivity.h>
#include <TrafficLight.h>

Connectivity::Connectivity(
    MqttClient *mqttClient,
    const String id,
    const String mqttInboundTopic,
    const String mqttOutboundTopic,
    const String mqttUsername,
    const String mqttPassword)
{
    // Set the MQTT client.
    setDeviceId(id);
    setMqttClient(mqttClient);
    setMqttInboundTopic(mqttInboundTopic);
    setMqttOutboundTopic(mqttOutboundTopic);

    // Each client must have a unique client ID.
    getMqttClient()->setId(getDeviceId());

    // Provide the username and password for authentication.
    getMqttClient()->setUsernamePassword(mqttUsername, mqttPassword);
}

String Connectivity::getDeviceId()
{
    return deviceId;
}

MqttClient *Connectivity::getMqttClient()
{
    return mqttClient;
}

String Connectivity::getMqttInboundTopic()
{
    return mqttInboundTopic;
}

String Connectivity::getMqttOutboundTopic()
{
    return mqttOutboundTopic;
}

void Connectivity::setDeviceId(String id)
{
    deviceId = id;
}

void Connectivity::setMqttClient(MqttClient *client)
{
    mqttClient = client;
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

void Connectivity::setupMQTT(const String mqttBroker, const uint mqttPort)
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

// Setup Network & MQTT access.
void Connectivity::setup(
    String ssid,
    String password,
    const String mqttBroker,
    const uint mqttPort)
{
    setupNetworkAccess(ssid, password);
    setupMQTT(mqttBroker, mqttPort);
}

TrafficPayload Connectivity::receiveMQTTData(int messageSize)
{
    String data;
    JsonDocument doc;
    TrafficPayload payload;

    // We received a message, print out the topic and contents.
    Serial.println("Received a message with topic '");
    Serial.print(getMqttClient()->messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to get the contents.
    while (getMqttClient()->available())
    {
        data += (char)getMqttClient()->read();
    }

    // Log the incoming data.
    Serial.println("The data is " + data);

    // Get the data from the string.
    deserializeJson(doc, data);

    // Populate the struct.
    payload.priority = doc["priority"];
    payload.timestamp = doc["timestamp"];
    payload.queue = doc["queue"];

    // Return the contents.
    return payload;
}

void Connectivity::sendTrafficState(TrafficState state)
{
    // Build the JSON object.
    String data;
    JsonDocument doc;

    doc["colour"] = state.colour;
    doc["duration"] = state.duration;

    // Convert the data to a string.
    serializeJson(doc, data);

    getMqttClient()->beginMessage(getMqttOutboundTopic());
    getMqttClient()->print(data);
    getMqttClient()->endMessage();
}
