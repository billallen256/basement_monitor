#include "temperature_humidity.h"

DHT dht(DHTPIN, DHTTYPE);

void setup_temperature_humidity() {
    dht.begin();
}