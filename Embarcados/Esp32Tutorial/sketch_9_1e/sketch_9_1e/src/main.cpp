#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {

  // Lê valor de toque referente ao jumper ligado ao pino T0 (GPIO4)
  Serial.printf("Touch value: %d\n", touchRead(T0)); 

  // Tempo entre medidas no serial
  delay(1000);
}
