#include <ArduinoMqttClient.h>
#include <WiFi.h>

void setupConnectivity(String ssid, String password)
{
    // Setup complete text.
    Serial.println("Mjolnir starting...");
    Serial.println();

    Serial.print("Mjolnir connecting to: ");
    Serial.print(ssid);
    Serial.println();
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.println("Wi-Fi connected.");
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.println();
}

void setupMQTT(MqttClient *mqttClient, String uuid, String broker, uint16_t port)
{
    // Each client must have a unique client ID
    mqttClient->setId(uuid);

    Serial.print("Attempting to connect to the MQTT broker: ");
    Serial.println(broker);

    if (!mqttClient->connect(broker.c_str(), port))
    {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient->connectError());

        while (1)
            ;
    }

    Serial.println("You're connected to the MQTT broker!");
    Serial.println();
}

void sendMessage(MqttClient *mqttClient, String topic, String message)
{
    mqttClient->beginMessage(topic);
    mqttClient->print(message);
    mqttClient->endMessage();
}
