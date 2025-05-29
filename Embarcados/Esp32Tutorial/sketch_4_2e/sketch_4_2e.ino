#define FRQ 1000
#define PWM_BIT 10


const byte led_pins [] = {23, 22, 21, 19, 18, 5, 4, 0, 2, 15};
const byte chns [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
const int dutys [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1023, 512, 256, 128, 64, 32, 16, 8, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Nleds;
const int delay_time = 75; 


void setup() {
  Nleds=sizeof(led_pins);
  for(int i=0; i<Nleds; i++){
    ledcAttachChannel(led_pins[i], FRQ, PWM_BIT, chns[i]);
  }
}

void loop() {
  for(int i=0; i<(2*Nleds); i++){
    for(int j=0; j<Nleds; j++){
      ledcWrite(led_pins[j], dutys[i+j]);
    }
    delay(delay_time);
  }
  for(int i=0; i<Nleds; i++){
    for(int j=Nleds-1; j>=0; j--){
      ledcWrite(led_pins[j], dutys[i + (Nleds - 1 - j)]);
    }
    delay(delay_time);
  }
}
