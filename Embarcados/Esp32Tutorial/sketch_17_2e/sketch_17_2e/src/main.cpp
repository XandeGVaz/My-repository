#include <Arduino.h>
#include <ESP32Servo.h>

// Defines
#define SIGNAL_PIN 15
#define ANALOG_PIN 13
#define MAX_ADC 4095 // nível adc máximo da esp 32
#define MIN_ADC 0

// Objeto Servo
Servo myServo;
int adcVal = 0;
int posServo = 0;

void setup(){

  // Frequência do motor do servo
  myServo.setPeriodHertz(50);

  // Configuração do servo
  myServo.attach(SIGNAL_PIN, 500, 2500);

  // Configuração da comunicação UART
  Serial.begin(115200);
}

void loop() {

  // Obtém-se nível ADC
  adcVal = analogRead(ANALOG_PIN);

  Serial.printf("ADC: %d ", adcVal);

  // Adquire posição atual de acordo com o valor ADC obtido
  posServo = map(adcVal, MIN_ADC, MAX_ADC, 0, 180);

  Serial.printf("Servo: %d graus\n", posServo);

  // Mudança de posição do servo
  myServo.write(posServo);

  // Tempo para servo chegar a posição determinada
  delay(15);
}

