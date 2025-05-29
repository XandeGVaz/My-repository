#include <Arduino.h>

// Defines
#define PIN_LED 13
#define TOUCH_VALUE 14    // valor do sensor para quando ha toque
#define NOTOUCH_VALUE 25  // valor do sensor para quando não ha toque

// Variáveis globais
/*Flag de processamento
* GRANDE IMPORTÂNCIA PARA SISTEMAS COMO ESSE
* -> Evita que o mesmo processo seja feito várias vezes sem necessidade
* -> Se ela não existisse, o micro trocaria a todo momento o estado do Led enquanto tivesse toque
* -> E caso não houvesse toque, o segundo escopo do loop seria realizado a todo momento sem necessidade
*Logo, com ela ha o resultado esperado e uma grande economia de processamento
*/
int processed = 0;

// Funções
void reverseGPIO(int pin);

void setup() {
  // Seta pino do led como saía do sistema
  pinMode(13, OUTPUT);
  
  // Iniciação de comunicação UART (serial)
  Serial.begin(115200);
}

/* Nesse programa consideraremos o detector de toque T0 (referente ao pino GPIO4)*/
void loop() {
  
  if(touchRead(T0) < TOUCH_VALUE){
    if(!processed){

      // Avisa detecção do toque no sensor
      Serial.printf("Toque detectado!\n");
      
      // Inverte estado do LED
      reverseGPIO(PIN_LED);

      // Avisa que o toque foi processado
      processed = 1;
    }
  }

  if(touchRead(T0) > NOTOUCH_VALUE){
    if(processed){

      // Avisa que o sensor de toque está disponível
      Serial.printf("Disnponível\n");

      // Avisa que o novo toque ainda não foi processado
      processed = 0;
    }
  }
}

// Função de inverter o estado do pino passado por parâmetro
void reverseGPIO(int pin){
  digitalWrite(pin, !digitalRead(pin));
}
