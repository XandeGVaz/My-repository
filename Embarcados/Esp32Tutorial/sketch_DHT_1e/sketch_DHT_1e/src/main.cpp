#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

/*===============================================================================*/
#define DHT_PIN 13
#define DHTTYPE DHT22 

/*===============================================================================*/
// Delay de funcionamento do sistema
uint32_t delayDHT;

/*===============================================================================*/
// Funções do sensor
sensor_t Sensor;
void setupDHT();
void updateValueDHT();

/*===============================================================================*/
// Sensor DHT11
DHT_Unified DHT(DHT_PIN, DHTTYPE);

//Temperatura e umidade
String Temperature; 
String Humidity;

/*===============================================================================*/
void setupDHT(){
  DHT.begin();
  DHT.temperature().getSensor(&Sensor);
  DHT.humidity().getSensor(&Sensor);
  delayDHT = Sensor.min_delay / 1000;
}

void updateValueDHT(){
  
  sensors_event_t event;
  float temperature, humidity;

  DHT.temperature().getEvent(&event);
  if(isnan(event.temperature)) temperature = -1;
  else temperature = event.temperature;

  DHT.humidity().getEvent(&event);
  if(isnan(event.relative_humidity)) humidity = -1;
  else humidity = event.temperature;

  Temperature = String(temperature); Humidity = String(humidity);
}

void setup() {
  Serial.begin(115200);
  setupDHT();
}

void loop() {
  updateValueDHT();
  Serial.println("Temperature: " + Temperature + "ºC  Humidity: " + Humidity + "%");
  delay(1000);
}

