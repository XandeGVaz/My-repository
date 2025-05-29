#include <Arduino.h>

#define PIN_BUTTON 4  // pino do circuito do botão
#define PIN_BUZZER 13 // pino do circuito do buzzer
#define CHN 0         // canal pwm
#define BFREQ 2000    // frequẽncia associada ao PWM

void alert(); // função responsável pela oscilação da frequência PWM da alimentação do buzzer PASSIVO

void setup() {
  
  pinMode(PIN_BUTTON, INPUT);     // setagem do pino de entrada do sistema

  ledcAttachPin(PIN_BUZZER, CHN); // atrela canal PWM ao pino do buzzer
  
  ledcWriteTone(CHN, BFREQ); 
  delay(300);                     // som é ativado por 0,3 s, com 2 KHZ de frequência 

}

void loop() {

  if(digitalRead(PIN_BUTTON) == LOW)  // caso o botão seja ativado há saída de som do buzzer
    alert();

  else
    ledcWriteTone(CHN, 0);             // não há saída de som do buzzer (sinal PWM desativado -> f = 0 khz)

}

void alert() {

  // variável do valor de seno ao longo de um período
  float sinVal;

  // valor da frequência do som do buzzer
  int toneVal;
  

  for(int t=0; t<360; t += 90){
    
    sinVal = sin(t * (PI/180));       // cálculo do seno nesse intervalo de tempo
    toneVal = BFREQ + 500 * sinVal;   // cálculo da frequência do som do buzzer em um determinado intervalo de tempo
    
    ledcWriteTone(CHN, toneVal);      // definição do sinal PWM do pino associado ao circuito do buzzer
    delay(90);                        // observe que os incrementos do for e o delay tem o mesmo valor !
  }
}
