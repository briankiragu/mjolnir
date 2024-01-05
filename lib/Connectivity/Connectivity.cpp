#include <WiFi.h>

#include <Arduino_JSON.h>
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
    setMqttClient(mqttClient);

    // Each client must have a unique client ID.
    getMqttClient()->setId(deviceId);

    // Provide the username and password for authentication.
    getMqttClient()->setUsernamePassword(mqttUsername, mqttPassword);
}

MqttClient *Connectivity::getMqttClient()
{
    return mqttClient;
}

void Connectivity::setMqttClient(MqttClient *client)
{
    mqttClient = client;
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
        "Device ID '" + deviceId +
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
        "Device ID '" + deviceId +
        "' is successfully connected to the MQTT broker!");

    Serial.println(
        "Device ID '" + deviceId +
        "' is subscribing to topic '" + mqttInboundTopic + "'");

    // Subscribe to the inbound topic to receive updates.
    getMqttClient()->subscribe(mqttInboundTopic);
}

TrafficPayload Connectivity::receiveMQTTData(int messageSize)
{
    // Variable to store the incoming message.
    String dataAsString;
    JSONVar dataAsJSON;
    TrafficPayload dataAsStruct;

    // We received a message, print out the topic and contents.
    Serial.println("Received a message with topic '");
    Serial.print(getMqttClient()->messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to get the contents.
    while (getMqttClient()->available())
    {
        dataAsString += (char)getMqttClient()->read();
    }

    // Log the incoming data.
    Serial.println("The data is " + dataAsString);

    // Parse the JSON.
    dataAsJSON = JSON.parse(dataAsString);

    // Populate the struct.
    dataAsStruct.priority = dataAsJSON["priority"];
    dataAsStruct.timestamp = dataAsJSON["timestamp"];
    dataAsStruct.queue = dataAsJSON["queue"];

    // Return the contents.
    return dataAsStruct;
}

void Connectivity::sendTrafficState(TrafficState state)
{
    // Build the JSON object.
    JSONVar data;
    data["colour"] = state.colour;
    data["duration"] = state.duration;

    getMqttClient()->beginMessage(mqttOutboundTopic);
    getMqttClient()->print(JSON.stringify(data));
    getMqttClient()->endMessage();
}
