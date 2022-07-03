// based on https://docs.arduino.cc/tutorials/ethernet-shield-rev2/UDPSendReceiveString

#include <Arduino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include "gauge.h"
#include "serial.h"
#include "temperature_humidity.h"

byte localMac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x55, 0xB1};
IPAddress localIp(192, 168, 1, 130);
uint16_t localPort = 8888;

IPAddress remoteIp(192, 168, 1, 117);
uint16_t remotePort = 8125;

char sendBuffer[50];
EthernetUDP Udp;

void setup_ethernet() {
  Ethernet.init(10);
  Ethernet.begin(localMac, localIp);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  Udp.begin(localPort);
}

void setup() {
  setup_serial();
  setup_temperature_humidity();
  Serial.println("setup_temperature_humidity() complete");
  setup_ethernet();
  Serial.println("setup_ethernet() complete");
}

void send_temperature() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Got NaN temperature");
    return;
  }

  Serial.println(temperature);
  Gauge_str(sendBuffer, "basement.temp", (int)(temperature*100));
  Serial.println(sendBuffer);
  Udp.beginPacket(remoteIp, remotePort);
  Udp.write(sendBuffer);
  Udp.endPacket();
}

void send_humidity() {
  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("Got NaN humidity");
    return;
  }

  Serial.println(humidity);
  Gauge_str(sendBuffer, "basement.humid", (int)(humidity*100));
  Serial.println(sendBuffer);
  Udp.beginPacket(remoteIp, remotePort);
  Udp.write(sendBuffer);
  Udp.endPacket();
}

void loop() {
  send_temperature();
  delay(5000);
  send_humidity();
  delay(10*60*1000UL);
}