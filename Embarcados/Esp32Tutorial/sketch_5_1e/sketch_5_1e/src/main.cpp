#include <Arduino.h>

#define FRQ 1000
#define PWM_BIT 8 //Necessário que seja 8, pois cada cor do rgb (red green ou blue) tem intensidade de 0 a 255 e (o sistema possui 2^8 * 2^8 * 2^8 cores possíveis)

const byte rgb_pins [] = {2, 0, 4}; //pinos das entradas red green e blue respectivamentte
const byte chns [] = {0, 1, 2}; //canais de PWM
volatile int red, green, blue; //três inteiros "uint32_t"

void setColor(int r, int g, int b);

/*
  Anexa canais aos pinos rgb
  Como cada canal terá uma diferente dutty em cada momentto, é necessário um canal para cada pino 
*/
void setup() {
  for(int i=0; i<3; i++){
    ledcAttachPin(rgb_pins[i], chns[i]);
    ledcSetup(chns[i], FRQ, PWM_BIT);     //configura os canais dos pinos rgb//
  }
}

void loop() {
  red=random(0,256); //cria um número randômico entre 0 e 255
  green=random(0,256);
  blue=random(0,256);
  setColor(red,green,blue);
  delay(200);
}

void setColor(int r, int g, int b){
  ledcWrite(rgb_pins[0],r);
  ledcWrite(rgb_pins[1],g);
  ledcWrite(rgb_pins[2],b);
}
