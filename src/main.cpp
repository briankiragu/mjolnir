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

void setup()
{
    // Serial output.
    Serial.flush();
    Serial.begin(115200);
    Serial.println();

    // Setup the traffic light LEDs.
    trafficLight.setup();

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

void onMqttMessage(int messageSize)
{
    JSONVar payload = receivePayload(&mqttClient, messageSize);

    trafficLight.setStatus(AMBER);
    trafficLight.setDuration(payload["duration"]);

    trafficLight.turnColour(trafficLight.getStatus());
    sendPayload(&mqttClient, mqttOutboundTopic, trafficLight.getStatus(), trafficLight.getDuration());
    delay(trafficLight.getDuration());
}

void updateTraffic(TrafficStatuses status, uint16_t duration)
{
    // Update the traffic light's status.
    trafficLight.setStatus(status);
    trafficLight.setDuration(duration);

    // Turn the lights RED.
    trafficLight.turnColour(trafficLight.getStatus());

    // Send the data over MQTT.
    sendPayload(
        &mqttClient,
        mqttOutboundTopic,
        trafficLight.getStatus(),
        trafficLight.getDuration());

    // Set the colour for the duration specified.
    delay(trafficLight.getDuration());
}

void loop()
{
    // Call poll() regularly to allow the library
    // to send MQTT keep alives
    // which avoids being disconnected by the broker.
    mqttClient.poll();

    // Check if there is an inbound message.
    mqttClient.onMessage(onMqttMessage);

    // Update the traffic light and status to RED.
    updateTraffic(RED, 3000);

    // Update the traffic light and status to AMBER.
    updateTraffic(AMBER, 2000);

    // Update the traffic light and status to GREEN.
    updateTraffic(GREEN, 5000);
}
