#define PIN_LED 2
#define CHN 0 // canal PWM
#define FRQ 1000 // frequência definida no PWM
#define PWM_BIT 8 //precisão em bits 2^8 -> 0% a 100% <-> 0 a 255

void setup() {
  ledcAttachChannel(PIN_LED,FRQ,PWM_BIT,CHN); //conecta pino ao canal de PWM e configura os padões desse canal
}

void loop() {
  for(int i=0; i<255; i++){
    ledcWrite(PIN_LED,i); //define o duty(i) atual do pulso 
    delay(5);
  }
  for(int i=0255; i>=0; i--){
    ledcWrite(PIN_LED,i);
    delay(5);
  }
}
