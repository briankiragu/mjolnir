#include <Arduino.h>
#include <ArduinoMqttClient.h>
#include <WiFi.h>

#include "secrets.h"

#include <Connectivity.h>
#include <TrafficLights.h>

const uint8_t RED_PIN = 13;
const uint8_t GREEN_PIN = 12;
const uint8_t BLUE_PIN = 14;

// Device ID.
String deviceId = DEVICE_ID;

// Network Access Credentials.
String networkSSID = NETWORK_SSID;
String networkPassword = NETWORK_PASS;

// MQTT Credentials.
String mqttUsername = MQTT_USERNAME;
String mqttPassword = MQTT_PASSWORD;
String mqttBroker = MQTT_BROKER;
uint16_t mqttPort = MQTT_PORT;

String mqttInboundTopic = MQTT_INBOUND_TOPIC;
String mqttOutboundTopic = MQTT_OUTBOUND_TOPIC;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

void setup()
{
    // Serial output.
    Serial.begin(115200);

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
        turnRed(RED_PIN, GREEN_PIN, BLUE_PIN);
        sendMessage(&mqttClient, mqttOutboundTopic, "RED");
        delay(1000);

        // Turn the lights AMBER.
        turnAmber(RED_PIN, GREEN_PIN, BLUE_PIN);
        sendMessage(&mqttClient, mqttOutboundTopic, "AMBER");
        delay(1000);

        // Turn the lights AMBER.
        turnGreen(RED_PIN, GREEN_PIN, BLUE_PIN);
        sendMessage(&mqttClient, mqttOutboundTopic, "GREEN");
        delay(1000);
    }
}
