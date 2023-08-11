#include "UbidotsESPMQTT.h"
#define TOKEN "BBFF-gkf4dxHCluVjAP4o7qbwSnDYJNYOb5"
#define WIFINAME "Priyanka"
#define WIFIPASS ""
Ubidots client(TOKEN);
const int trigPin = D5;
const int echoPin = D4;
const int led = D2;
uint8_t buzz = D7;
long duration;
float distance;
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
void setup() {
  client.setDebug(true);
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(led, HIGH);
  
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }
void loop() {
  if(!client.connected()){
      client.reconnect();
      }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  client.add("distance", distance);
   if (distance < 10){
    tone(buzz,1000);
    digitalWrite(led, HIGH);
    delay(2000);
    noTone(buzz);
    digitalWrite(led, LOW);
  }  
  client.ubidotsPublish("contactless-bell");
  client.loop();
  delay(1000);
}
