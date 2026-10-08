#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// ====== CHANGE THIS to a unique ID, same one goes in the dashboard Settings ======
#define DEVICE_ID "homesec-demo-x7k2"

#define PIR_PIN 27
#define DOOR_PIN 26   // button pressed = door OPEN
#define DHT_PIN 15
#define BUZZ_PIN 25
#define LED_PIN 2

const char* ssid = "Wokwi-GUEST";
const char* broker = "broker.hivemq.com";
String tStatus = String(DEVICE_ID) + "/status";
String tCmd = String(DEVICE_ID) + "/cmd";

WiFiClient net;
PubSubClient mqtt(net);
DHT dht(DHT_PIN, DHT22);

bool armed = false, alarm = false;
unsigned long lastPub = 0;

void onMsg(char* topic, byte* p, unsigned int len) {
  String m;
  for (unsigned i = 0; i < len; i++) m += (char)p[i];
  if (m == "ARM") armed = true;
  if (m == "DISARM") { armed = false; alarm = false; }
  if (m == "SIREN_OFF") alarm = false;
  if (m == "TEST") alarm = true;
}

void connectAll() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, "", 6);
    while (WiFi.status() != WL_CONNECTED) delay(300);
  }
  while (!mqtt.connected()) {
    if (mqtt.connect(("esp-" + String(random(0xffff), HEX)).c_str())) mqtt.subscribe(tCmd.c_str());
    else delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(DOOR_PIN, INPUT_PULLUP);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(onMsg);
}

void loop() {
  connectAll();
  mqtt.loop();

  bool motion = digitalRead(PIR_PIN);
  bool doorOpen = !digitalRead(DOOR_PIN);

  // Trigger alarm only when system is armed
  if (armed && (motion || doorOpen)) alarm = true;

  digitalWrite(LED_PIN, alarm);
  if (alarm) tone(BUZZ_PIN, 1000); else noTone(BUZZ_PIN);

  if (millis() - lastPub > 1000) {
    lastPub = millis();
    float t = dht.readTemperature(), h = dht.readHumidity();
    String j = "{\"armed\":" + String(armed) + ",\"alarm\":" + String(alarm) +
               ",\"motion\":" + String(motion) + ",\"door\":" + String(doorOpen) +
               ",\"temp\":" + String(isnan(t) ? 0 : t, 1) +
               ",\"hum\":" + String(isnan(h) ? 0 : h, 0) + "}";
    mqtt.publish(tStatus.c_str(), j.c_str());
    Serial.println(j);
  }
}
