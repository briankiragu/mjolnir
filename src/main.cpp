#include <Arduino.h>
#include <WiFi.h>

#include <ArduinoMqttClient.h>

#include "secrets.h"

#include <TrafficLights.h>
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

TrafficStatuses status;

void setup()
{
    // Serial output.
    Serial.flush();
    Serial.begin(115200);
    Serial.println();

    // Setup the traffic light LEDs.
    setupTrafficLights(RED_PIN, GREEN_PIN, BLUE_PIN);

    // Setup the Wi-Fi connection.
    setupNetworkAccess(networkSSID, networkPassword);

    // Setup the MQTT connection.
    setupMQTT(
        &mqttClient,
        deviceId,
        mqttUsername,
        mqttPassword,
        mqttBroker,
        mqttPort,
        mqttInboundTopic);

    // Setup complete text.
    Serial.println("Setup complete. Mjolnir is starting.");
}

void loop()
{
    // call poll() regularly to allow the library
    // to send MQTT keep alives
    // which avoids being disconnected by the broker.
    mqttClient.poll();

    // Parse any received messages.
    int messageSize = mqttClient.parseMessage();

    // If any messages came in, processes them. If not,
    // trigger statuses as usual.
    if (messageSize)
    {
        receiveMessage(&mqttClient, messageSize);
    }
    else
    {
        // Turn the lights RED.
        status = RED;
        turnRed(RED_PIN, GREEN_PIN, BLUE_PIN);
        sendStatus(&mqttClient, mqttOutboundTopic, status);
        delay(1000);

        // Turn the lights AMBER.
        status = AMBER;
        turnAmber(RED_PIN, GREEN_PIN, BLUE_PIN);
        sendStatus(&mqttClient, mqttOutboundTopic, status);
        delay(1000);

        // Turn the lights AMBER.
        status = GREEN;
        turnGreen(RED_PIN, GREEN_PIN, BLUE_PIN);
        sendStatus(&mqttClient, mqttOutboundTopic, status);
        delay(1000);
    }
}
