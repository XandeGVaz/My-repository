#include <Arduino.h>

// Defines
#define PIN_ANALOG_IN 4  // pino de entrada analógica (pino 3 do potenciômetro) - ADC2-CH0

// Não é necessário configurar pinos para ADC e DAC
void setup() {
  Serial.begin(115200); // taxa da transmissão do monitor serial
}

void loop() {

  // Variáveis
  int adcVal; // valor digital lido com ADC
  int dacVal; // valor análogico a ser escrito cm DAC
  double voltage; // tensão do potênciometro

  // Conversão ADC (entrada)
  /* Leitura do nível digital do pino de entrada de valor analógico de tensão
  *  ADC2 é desativado quando utilizamos o wifi da ESP32
  */
  adcVal = analogRead(PIN_ANALOG_IN);

  // Obtenção da voltagem do potenciômetro
  /* tendo que adcValue = analogicVoltage / (3.3/4096) */
  voltage = ((double)adcVal/4095) * 3.3;

  // Conversão DAC (saída)
  /* Basicamente mapeia um número para o "range", ou seja, para a precisção do outro
  *Valor low vai para low, do meio para do meio e high para high 
  */
  dacVal = map(adcVal, 0, 4095, 0 , 255);
  dacWrite(DAC1, dacVal); // converte sinal digital mapeado para analógico no pino 25 (DAC1)
                          

  // Obtenção dos valores no munitor serial
  Serial.printf("ADC = %d V, Voltage = %.2f V, DAC = %d\n", adcVal, voltage, dacVal);

  // Delay de medida
  delay(500);

}

