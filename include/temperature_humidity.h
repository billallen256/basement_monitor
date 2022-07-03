#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2

#define DHTTYPE DHT11

extern DHT dht;

void setup_temperature_humidity();
float get_temperature();
float get_humidity();
void print_sensor_info();