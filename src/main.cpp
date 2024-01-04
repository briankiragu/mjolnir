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
const uint16_t mqttPort = MQTT_PORT;

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

void updateTraffic(TrafficColours colour, uint16_t duration)
{
    // Initialise the payload.
    MQTTPayload payload = {colour, duration};

    // Update the traffic light's colour to the colour.
    trafficLight.updateColourAndDuration(colour, duration);

    // Send the data over MQTT.
    connection.sendMQTTPayload(payload);
}

void onMqttMessage(int messageSize)
{
    // Receive, parse and return the incoming data from MQTT.
    MQTTPayload payload = connection.receiveMQTTPayload(messageSize);

    // Update the traffic light's colour to the colour.
    updateTraffic((TrafficColours)payload.colour, payload.duration);
}

void setup()
{
    // Serial output.
    Serial.flush();
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
    // Call poll() regularly to allow the library
    // to send MQTT keep alives
    // which avoids being disconnected by the broker.
    connection.getMqttClient()->poll();

    // Check if there is an inbound message.
    connection.getMqttClient()->onMessage(onMqttMessage);

    // Update the traffic light and colour to RED.
    updateTraffic(RED, 3000);

    // Update the traffic light and colour to AMBER.
    updateTraffic(AMBER, 2000);

    // Update the traffic light and colour to GREEN.
    updateTraffic(GREEN, 5000);
}
