#define PIN_BUZZER 13   // Pino do buzzer ativo
#define PIN_BUTTON 4   // Pino do botão de de entrada -> através dele saberemos se devemos ativar o transistor

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  if(digitalRead(PIN_BUTTON) == LOW)
    digitalWrite(PIN_BUZZER, HIGH);
  else
    digitalWrite(PIN_BUZZER, LOW);
}