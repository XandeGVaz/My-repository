
// Defines
#define ANALOGIC_INPUT_PIN 4 // pino de entrada analógica para ADC
#define PIN_LED 25           // pino de saída para ativamente do led
#define CH 0                 // canal PWM

void setup() {

  // Ligação do canal PWM 0 ao pino do led
  ledcAttachChannel(PIN_LED, 1000, 12, CH);

}

void loop() {
  
  // Valor adc obtido do pino de leitura analógica para digital  
  int adcVal = analogRead(ANALOGIC_INPUT_PIN); // leitura adc 
  
  // Valor pwm (deve ser correspondente ao valor adc lido, para que seja modulado no led usando PWM)
  int pwmVal = adcVal;

  // Uso de PWM para construir sinal analógico
  ledcWrite(PIN_LED, pwmVal);

  // Tempo entre leituras do ADC
  delay(10);

}