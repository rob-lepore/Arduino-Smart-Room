#include <WiFi.h>
#include "PubSubClient.h"
#include <WiFiClientSecure.h>
#include "Light.h"
#include "Photoresistor.h"
#include "Pir.h"


/*  WiFi and MQTT parameters  */
const char* ssid = "Roberto's Galaxy A52s 5G";
const char* password = "password";
const char* mqttServer = "62d6711e8bac4a34999924c6119ec7da.s2.eu.hivemq.cloud";
const int mqttPort = 8883;
const char* mqttUser = "esiot-2022-1";
const char* mqttPassword = "Prova123";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void connectMQTTBroker() {
  espClient.setInsecure();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, state=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  
}


void publish(const char* topic, const char* message) {
  if (client.publish(topic, message)) {
    //Serial.println("Publish Successful");
  } else {
    Serial.println("Publish Failed");
  }
}



/**   Tasks   **/

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

Light* light;
Photoresistor* photores;
Pir* pir;

double lightValue = 0.0;
bool movement = false;

void ledTask(void* parameter) {
  while (1) {
    if (movement) {
      light->turnOn();
    } else {
      light->turnOff();
    }
    delay(1000);
  }
}

void lightLevelTask(void* parameter) {
  while (1) {
    lightValue = photores->getLightLevel();
    delay(1000);
  }
}

void movementSensorTask(void* parameter) {
  while (1) {
    movement = pir->detect();
    delay(1000);
  }
}

/******************/




void setup() {
  Serial.begin(115200);

  connectWiFi();
  connectMQTTBroker();

  /* sensors init */
  light = new Light(4);
  photores = new Photoresistor(1);
  pir = new Pir(2, 10);

  xTaskCreatePinnedToCore(ledTask, "Task1", 10000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(lightLevelTask, "Task2", 10000, NULL, 1, &Task2, 1);
  xTaskCreatePinnedToCore(movementSensorTask, "Task3", 10000, NULL, 1, &Task3, 1);
  delay(500);
}

void loop() {
  client.loop();

  if (client.connected()) {

    char lightStr[10], mvmStr[10];
    snprintf(lightStr, 10, "%f", lightValue);
    snprintf(mvmStr, 10, "%d", movement);

    publish("Light Level", lightStr);
    publish("Movement", mvmStr);

    delay(1000); 
  }
}