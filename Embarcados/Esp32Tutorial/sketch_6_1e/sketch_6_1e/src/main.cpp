#include <Arduino.h>
#define PIN_BUZZER 13   // Pino do buzzer ativo
#define PIN_BUTTON 4   // Pino do botão de de entrada -> através dele saberemos se devemos ativar o transistor

void setup() {
  
  pinMode(PIN_BUZZER, OUTPUT);    // circuito do buzzer gera o sinal de saída com base no funcionamento de outro circuito (o circuito de entrada) 
 
  pinMode(PIN_BUTTON, INPUT);     // circuito da chave recebe o sinal de entrada (pressionamento do botão) e com base nisso define o nível de tensão como low(botão pressionado -> gera curto) ou high 

}

void loop(){
  
  if(digitalRead(PIN_BUTTON) == LOW) // se botão está pressionado -> buzzer é ativado
    digitalWrite(PIN_BUZZER, HIGH);
  
  else
    digitalWrite(PIN_BUZZER, LOW);  // caso contrário, buzzer permanece inativo
}