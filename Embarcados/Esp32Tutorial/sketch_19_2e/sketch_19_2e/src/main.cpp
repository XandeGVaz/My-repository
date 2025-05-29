#include <Arduino.h>
#include <UltrasonicSensor.h>

// Temperatura Ambiente
#define AMB_TEMP 22

// Pinos de conexão da esp com o sensor ultrassonico
#define TRIGGER_PIN 13
#define ECHO_PIN 14

// Objeto sensor ultrassônico
UltrasonicSensor ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup() {
  // Iniciação do monitor serial
  Serial.begin(115200);

  // Set da temperatura no sensor
  ultrasonic.setTemperature(AMB_TEMP);
}

void loop() {
  
  // Impressão no monitor serial da distância entre o sensor e o primeiro obstáculo (em cm)
  Serial.printf("Distance: %d cm\n", ultrasonic.distanceInCentimeters());
  
  // Delay de 1s entre medições
  delay(1000);
} 
