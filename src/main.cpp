#include <Arduino.h>
#include <WiFi.h>

#include <Arduino_JSON.h>
#include <ArduinoMqttClient.h>

#include "secrets.h"

#include <TrafficLight.h>
#include <Connectivity.h>

const uint8_t RED_PIN = 13;
const uint8_t GREEN_PIN = 12;
const uint8_t BLUE_PIN = 14;

// Device ID.
const String deviceId = DEVICE_ID;

// Network access credentials.
const String networkSSID = NETWORK_SSID;
const String networkPassword = NETWORK_PASS;

// MQTT credentials.
const String mqttUsername = MQTT_USERNAME;
const String mqttPassword = MQTT_PASSWORD;
const String mqttBroker = MQTT_BROKER;
const uint mqttPort = MQTT_PORT;

// MQTT topics.
const String mqttInboundTopic = MQTT_INBOUND_TOPIC;
const String mqttOutboundTopic = MQTT_OUTBOUND_TOPIC;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

TrafficLight trafficLight(RED_PIN, GREEN_PIN, BLUE_PIN);
Connectivity connection(
    &mqttClient,
    deviceId,
    mqttInboundTopic,
    mqttOutboundTopic,
    mqttUsername,
    mqttPassword);

void onMqttMessage(int messageSize)
{
    // Receive, parse and return the incoming data from MQTT.
    MQTTPayload data = connection.receiveMQTTData(messageSize);

    // Loop through the incoming traffic queue.
    for (size_t i = 0; i < sizeof(data.payload.queue); i++)
    {
        // Update the traffic light's colour to the colour.
        trafficLight.updateTraffic(data.payload.queue[i]);

        // Send the data over MQTT.
        connection.sendTrafficState(trafficLight.getState());
    }
}

void setup()
{
    // Serial output.
    Serial.begin(115200);
    Serial.println();

    // Setup the traffic light LEDs.
    trafficLight.setup();

    // Setup the Wi-Fi connection.
    connection.setupNetworkAccess(networkSSID, networkPassword);

    // Setup the MQTT connection.
    connection.setupMQTT(mqttBroker, mqttPort);

    // Setup complete text.
    Serial.println("Setup complete. Mjolnir is starting.");
}

void loop()
{
    // Call poll() regularly to allow the library to send 
    // MQTT keep-alives which avoids being disconnected by the broker.
    connection.getMqttClient()->poll();

    // Check if there is an inbound message.
    connection.getMqttClient()->onMessage(onMqttMessage);
}
