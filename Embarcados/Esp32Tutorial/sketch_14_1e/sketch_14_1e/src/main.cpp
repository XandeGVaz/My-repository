#include <Arduino.h>

// Defines
#define LATCH_PIN 12      // ST_CP (GPIO12) em 74HC595
#define CLOCK_PIN 13      // SH_CP (GPIO11) em 74HC595
#define DATA_PIN 14       // DS (GPIO14) em 74HC595

// Função de escrever dado no CI (74HC595) para que seja decodificado para sua saída  (8 bits)
void writeTo595(byte order, byte value);

void setup() {
// ura os pinos de controle do CI como saídas da ESP
pinMode(LATCH_PIN, OUTPUT);
pinMode(CLOCK_PIN, OUTPUT);
pinMode(DATA_PIN, OUTPUT);

}

void loop() {

  // Valor a ser passado para CI começa em 0000 0001_2
  byte x = 0x01;
  
  for(int i = 0; i < 8; i++){

    // Escreve valor no CI (que já é repassado para os leds)
    writeTo595(LSBFIRST, x);
    
    // Shift para esquerda (operação bit a bit)
    x <<= 1;
    
    // Delay para visualização
    delay(50);
  }
  
  // como x = 0x00 nesse estágio (shift ocorreu 8 vezes) 
  x = 0X10;


  for(int j = 0; j < 8; j++){

    // Escreve valor no CI (que já é repassado para os leds)
    writeTo595(LSBFIRST, x);
    
    // Shift para direita (operação bit a bit)
    x >>= 1;

    // Delay para visualização
    delay(50);
  }

  delay(100);
}

void writeTo595(byte order, byte value){

  /* Desabilitação da atualização do output do CI para atualização do dado de entrada
  *   EVITA ERROS -> sem isso, o dado nunca é atualizado
  */
  digitalWrite(LATCH_PIN, LOW);

  // Shift do dado para o pino de dado (inteiro) de entrada do CI (DATA_PIN)
  shiftOut(DATA_PIN /*Pino que recebe value (pode ser inteiro)*/, CLOCK_PIN /*Clock de borda positiva*/, 
  order /*Ordem de passagem dos bits*/, value);

  // Habilitação da atualização do output do CI
  digitalWrite(LATCH_PIN, HIGH);

}
