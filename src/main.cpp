#include <Arduino.h>
#include <WiFi.h>

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

TrafficStatuses status;
uint16_t duration;

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

    // Turn the lights RED.
    status = RED;
    duration = 3000;
    turnColour(RED_PIN, GREEN_PIN, BLUE_PIN, status);
    sendPayload(&mqttClient, mqttOutboundTopic, status, duration);
    delay(duration);

    // Turn the lights AMBER.
    status = AMBER;
    duration = 2000;
    turnColour(RED_PIN, GREEN_PIN, BLUE_PIN, status);
    sendPayload(&mqttClient, mqttOutboundTopic, status, duration);
    delay(duration);

    // Turn the lights GREEN.
    status = GREEN;
    duration = 5000;
    turnColour(RED_PIN, GREEN_PIN, BLUE_PIN, status);
    sendPayload(&mqttClient, mqttOutboundTopic, status, duration);
    delay(duration);
}
