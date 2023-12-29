#include <Arduino.h>
#include <ArduinoMqttClient.h>
#include <WiFi.h>

#include "secrets.h"

#include <Connectivity.h>
#include <TrafficLights.h>

const uint8_t RED_PIN = 15;
const uint8_t GREEN_PIN = 2;
const uint8_t BLUE_PIN = 4;

// Device ID.
String deviceId = DEVICE_ID;

// Network Access Credentials.
String ssid = SECRET_SSID;
String password = SECRET_PASS;

// MQTT Credentials.
String broker = MQTT_BROKER;
uint16_t port = MQTT_PORT;
String topic = MQTT_TOPIC;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

void setup()
{
    // Serial output.
    Serial.begin(115200);

    // Setup the traffic light LEDs.
    setupTrafficLights(RED_PIN, GREEN_PIN, BLUE_PIN);

    // Setup the Wi-Fi connection.
    setupNetworkAccess(ssid, password);

    // Setup the MQTT connection.
    setupMQTT(&mqttClient, broker, port, deviceId, topic);
}

void loop()
{
    // call poll() regularly to allow the library
    // to send MQTT keep alives
    // which avoids being disconnected by the broker.
    mqttClient.poll();

    // Turn the lights RED.
    turnRed(RED_PIN, GREEN_PIN, BLUE_PIN);
    sendMessage(&mqttClient, topic, "RED");
    delay(1000);

    // Turn the lights AMBER.
    turnAmber(RED_PIN, GREEN_PIN, BLUE_PIN);
    sendMessage(&mqttClient, topic, "AMBER");
    delay(1000);

    // Turn the lights AMBER.
    turnGreen(RED_PIN, GREEN_PIN, BLUE_PIN);
    sendMessage(&mqttClient, topic, "GREEN");
    delay(1000);
}
