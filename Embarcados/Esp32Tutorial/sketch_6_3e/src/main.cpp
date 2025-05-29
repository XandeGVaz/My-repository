#include <Arduino.h>

/* O objetivo desse código é gerar um pulso com 50% de largura em PWM usando o próprio GPIO em vez da 
* funçãoledcWriteTone(), a qual possui bugs para determinados períodos do pulso menores que 20msg. Com 
* isso usaremos os pŕopios pinos de saída/entrada em conjunto com um temporizador para gerar os pulsos.
*/

#define PIN_BUTTON 4
#define PIN_BUZZER 13

// variável timer
hw_timer_t* timer = NULL;

// bit usado para verificar se timer está ativado
bool isAlerting = false;

// ativamento do buzeer
void alert();

// evento temporizado
void IRAM_ATTR ontimer() {
  // inverte o sinal do pino referente ao circuito do Buzzer
  digitalWrite(PIN_BUZZER, !digitalRead(PIN_BUZZER));
}


void setup() {
  
  // Input
  pinMode(PIN_BUTTON, INPUT);

  // Output 
  pinMode(PIN_BUZZER, OUTPUT);

  /*  Set da frequẽncia do temporizador 
  * Na esp32: clock ticks at 80 MHz / 80 = 1 MHz
  */
  timer = timerBegin(0, 80, true); // freq = 1 MHz

  // Anexa evento ontimer ao temporizador, realizando-o a cada interrupção
  timerAttachInterrupt(timer, &ontimer, true /*borda*/);

}

void loop() {

  if(digitalRead(PIN_BUTTON) == LOW){
    
    if(!isAlerting)   // se alert não está ativado
    { 
      // alert acaba de ser ativado
      isAlerting = true;

      // set do alarm para geração de um evento de 1 ms, com autoreload
      timerAlarmWrite(timer, 1000 /*Talarm = alarm_value * (1/ftimer) */, true);

      // começa em alarm
      timerAlarmEnable(timer);
    }
    
    alert();                               
  
  }
  
  else{
  
    if(isAlerting)  // se alert está ativado
    {
      // alert acaba de ser desativado
      isAlerting  = false;

      // desativa alarm
      timerAlarmDisable(timer);

      // desativa buzzer (pode estar ativado no momento de desativamento do alarm)
      digitalWrite(PIN_BUZZER, LOW);
    }
  
  }

}

void alert(){
  float sinVal;
  int toneVal;
  
  for(int t=0; t<360; t+=90)
  {
    sinVal = sin(t*(PI/180));     //  seno de t
    toneVal = 2000 + sinVal*500;  //  2000 + sin(t)*500 
    
    /*Observe que o objetivo era, através do timer, gerar uma PWM com 50% da largura de onda em relação ao 
    * gerado com ledcWriteTone(), por isso utilizamos alarm_value = 500000/toneval ao invés de 1000000/
    * toneVal, a medida em que isso gerará (em média) um pulso de f=4000Hz ao invés de 2000Hz.
    */
    timerAlarmWrite(timer, 500000/toneVal, true); //
    delay(90);
  }

}
