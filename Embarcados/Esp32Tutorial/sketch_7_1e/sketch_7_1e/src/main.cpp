#include <Arduino.h>

void setup() {

  // Iniciação da comunicação serial
  Serial.begin(115200);

  // Print de inicialização
  Serial.println("Inicializacao da ESP 32!");  
}

void loop() {

  /* millis()
  *   ->Saída: tempo total de funcionamento do programa em milessegundos 
  */

  // Print de tempo de funcionamento do programa
  Serial.printf("O programa está funcionando a %.1f s\n", millis()/1000.0f);
  delay(1000);
}

