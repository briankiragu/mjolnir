#include <ArduinoMqttClient.h>
#include <WiFi.h>

void setupNetworkAccess(String ssid, String password)
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

void setupMQTT(
    MqttClient *mqttClient,
    String broker,
    uint16_t port,
    String deviceId,
    String topic)
{
    // Each client must have a unique client ID
    mqttClient->setId(deviceId);

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

    Serial.print("Subscribing to topic: ");
    Serial.print(topic);
    Serial.println();

    // Subscribe to the same topic to receive updates.
    mqttClient->subscribe(topic);
}

void sendMessage(MqttClient *mqttClient, String topic, String message)
{
    mqttClient->beginMessage(topic);
    mqttClient->print(message);
    mqttClient->endMessage();
}

void receiveMessage(MqttClient *mqttClient, int messageSize)
{
    // We received a message, print out the topic and contents
    Serial.println("Received a message with topic '");
    Serial.print(mqttClient->messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttClient->available())
    {
        Serial.print((char)mqttClient->read());
    }
    Serial.println();
}
