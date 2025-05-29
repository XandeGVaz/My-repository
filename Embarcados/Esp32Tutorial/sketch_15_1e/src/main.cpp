#include <Arduino.h>

// Defines
#define LATCH_PIN 12      // ST_CP (GPIO12) em 74HC595
#define CLOCK_PIN 13      // SH_CP (GPIO11) em 74HC595
#define DATA_PIN 14       // DS (GPIO14) em 74HC595

// Configuração da saída para cada configuração do display
byte num[] = {
  0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
  0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e
};


// Função de escrever dado na saída do CI 
void write595(byte value);

// Configuração dos pinos de saída (correspondentes aos pinos de configuração do CI
void setup(){
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}


void loop(){

  // Escreve sequencialmente números no display
  for(int i = 0; i < 16; i++){
    write595(num[i]);
    delay(500);
  }

  delay(500);
}

// Escreve dado serial no CI, passando os valores dos bits para as saída paralelas
void write595(byte value){
  // Desabilita escrita de saída
  digitalWrite(LATCH_PIN, LOW);

  // Shift do dado serial do menor bit para o restante
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value);

  // Habilita escrita de saída
  digitalWrite(LATCH_PIN, HIGH);
}

/* Função shiftOut nativo do C -> Facilita entendimento do circuito*/
// void shiftOut(GPIO dataPin, GPIO clockPin, bool MSBFIRST, uint8_t command)
// {
//    for (int i = 0; i < 8; i++)
//    {
//        bool output = false;
//        if (MSBFIRST)
//        {
//            output = command & 0b10000000;
//            command = command << 1;
//        }
//        else
//        {
//            output = command & 0b00000001;
//            command = command >> 1;
//        }
//        writePin(dataPin, output);
//        writePin(clockPin, true);
//        sleep(1)
//        writePin(clockPin, false);
//        sleep(1)
//     }
// }