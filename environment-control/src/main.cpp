#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "secret.h"

const char* ROOM_NUMBER = "1";
IPAddress mqttServer(192,168,178,40);

WiFiClient espClient;
PubSubClient client(mqttServer, 1883, espClient);
long lastMsg = 0;
char msg[50];

bool windowState = false;

//function prototypes
void setup_wifi();
void setup_hardware();

void setup() {
	Serial.begin(115200);
	setup_wifi();
  setup_hardware();
}

void setup_wifi() {
	delay(10);
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(SSID);

	WiFi.begin(SSID, PSK);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}


void setup_hardware()
{
  pinMode(D2, INPUT_PULLUP);
}
  

void reconnect() {
	while (!client.connected()) {
		Serial.print("Reconnecting...");
		if (!client.connect("ESP8266Client")) {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" retrying in 5 seconds");
			delay(5000);
		}
	}
}
void loop() {

	if (!client.connected()) {
		reconnect();
	}
	client.loop();

  if(windowState != digitalRead(D2))
  {
    windowState = !windowState;
    String topic = String("/home/room") + ROOM_NUMBER + "/window";
    String value = String(digitalRead(D2));
    Serial.print("Publish message: " + value + " to " + topic);
    Serial.println(msg);
    client.publish((topic).c_str(), value.c_str());
  }
	delay(100);
}