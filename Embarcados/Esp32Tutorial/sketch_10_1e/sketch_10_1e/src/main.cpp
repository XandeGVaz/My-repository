#include <Arduino.h>

// Defines
#define ANALOGIC_INPUT_PIN 4 // pino de entrada analógica para ADC
#define PIN_LED 25           // pino de saída para ativamente do led
#define CH 0                 // canal PWM

void setup() {
  
  /* Configura canal CH de PWM (freqência e precisão) e liga ao pino PIN_LED
  *   ->OBS: em platform.ini tivemos que setar para utilizar biblioteca 3.0.2 do arduino
  */
  ledcAttachChannel(PIN_LED, 1000, 12, CH);

}

void loop() {
  
  // Valor adc obtido do pino de leitura analógica para digital  
  int adcVal = analogRead(ANALOGIC_INPUT_PIN); // leitura adc 
  
  // Valor pwm (deve ser correspondente ao valor adc lido, para que seja modulado no led usando PWM)
  int pwmVal = adcVal;

  /* Uso de PWM para construir sinal analógico
  *   ->OBBS: utilizando PWM conseguimos uma precisão maior que de 8 bits pro sinal analógico gerado
  * já que nesse caso a precisão do sinal analógico também é de 12 bits (a mesma do ADC da esp32)
  */
  ledcWrite(PIN_LED, pwmVal);

  // Tempo entre leituras do ADC
  delay(10);

}