#include <Arduino.h>

#define FRQ 1000
#define PWM_BIT 8 //Necessário que seja 8, pois cada cor do rgb (red green ou blue) tem intensidade de 0 a 255 e (o sistema possui 2^8 * 2^8 * 2^8 cores possíveis)

const byte rgb_pins [] = {2, 0, 4}; //pinos das entradas red green e blue respectivamentte
const byte chns [] = {0, 1, 2}; //canais de PWM

void setColor(long rgb);
long wheel(int pos);

/*
  Anexa canais aos pinos rgb
  Como cada canal terá uma diferente dutty em cada momentto, é necessário um canal para cada pino 
*/
void setup() {
  for(int i=0; i<3; i++){
    ledcAttachChannel(rgb_pins[i], FRQ, PWM_BIT, chns[i]);     //configura os canais dos pinos rgb//
  }
}

void loop() {
  for(int i=0; i<256; i++){
    setColor(wheel(i));
    delay(20);
  }
}

void setColor(long rgb){
  ledcWrite(rgb_pins[0], 255 - (rgb >> 16) & 0xff);
  ledcWrite(rgb_pins[1], 255 - (rgb >> 8) & 0xff);
  ledcWrite(rgb_pins[2], 255 - (rgb >> 0) & 0xff);
}

long wheel(int pos) { //Retorna valor hexadecimal da cor xAABBCC AA-red, BB-green CC-blue
  long WheelPos = pos % 0xff;
  if (WheelPos < 85) {
    return ((255 - WheelPos * 3) << 16) | ((WheelPos * 3) << 8);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return (((255 - WheelPos * 3) << 8) | (WheelPos * 3)); 
  } else {
    WheelPos -= 170;
    return ((WheelPos * 3) << 16 | (255 - WheelPos * 3));
  }
}