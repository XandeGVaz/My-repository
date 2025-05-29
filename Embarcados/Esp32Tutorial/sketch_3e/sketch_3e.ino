static byte led_pin[] = {23,22,21,19,18,5,4,0,2,15};
static int Nled = sizeof(led_pin);

void setup() {
  for(int i=0; i<Nled; i++) pinMode(led_pin[i],OUTPUT);
}

void loop() {
  for(int i=0; i<Nled; i++){
    digitalWrite(led_pin[i],HIGH);
    delay(75);
    digitalWrite(led_pin[i],LOW);
  }
  for(int i=Nled-1; i>=0; i--){
    digitalWrite(led_pin[i],HIGH);
    delay(75);
    digitalWrite(led_pin[i],LOW);
  }
}
