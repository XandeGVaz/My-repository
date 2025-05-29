#include <Arduino.h>
#include <ESP32Servo.h>

// Defines
#define SIGNAL_PIN 15

// Objeto Servo
Servo myServo;

void setup() {

  // Frequência do motor do servo
  myServo.setPeriodHertz(50);
  
  // Inicialização do servo, anexando canal de sinal e definindo os níveis mínimo e máximo
  myServo.attach(SIGNAL_PIN, 500, 2500);
}

void loop() {

  // Rotação de avanço do servo
  for(int posVal=0; posVal <= 180; posVal++){
    myServo.write(posVal);
    delay(15);
  }

  // Rotação de retorno do servo
  for(int posVal=180; posVal >= 0; posVal--){
    myServo.write(posVal);
    delay(15);

  }

}
