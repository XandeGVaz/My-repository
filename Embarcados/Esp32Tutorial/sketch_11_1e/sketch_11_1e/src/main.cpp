#include <Arduino.h>

// Defines de valores
#define PIN_LED 25        // pino de saída para o led
#define PIN_ANALOG_IN 4   // pino de leitura adc
#define CH 0              // canal PWM para modulação de sinal analógico
#define MAX_LIGHT 2048    // nível de luz máximo do fotorresistor
#define MIN_LIGHT 0     // nível de luz mínima do fotorresistor

// Define de operação para verificar se um valor (amt) está dentro da faixa esperada (low, high)
#define constrain(amt, low, high) (amt < low) ? low : ((amt > high) ? high : amt) 


void setup() {
  // Configura PWM e anexa canal ao pino do led
  ledcAttachChannel(PIN_LED, 1000, 12, CH);
}

void loop() {
  // Obtenção do ADC do fotorresistor
  int adcVal = analogRead(PIN_ANALOG_IN);
  
  // Mapeamento do taxa de pwm (duty) com base nos possíveis níveis de luminosidade
  int pwmVal = map(constrain(adcVal, MIN_LIGHT, MAX_LIGHT), MIN_LIGHT, MAX_LIGHT, 0, 4095);
  
  // Geração do sinal analógico com pwm
  ledcWrite(PIN_LED, pwmVal);
}