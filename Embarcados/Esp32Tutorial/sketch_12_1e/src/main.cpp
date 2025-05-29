#include <Arduino.h>

// Defines
#define ANALOG_PIN_IN 4
#define VMAX 3.3              // tensão de alimentação do circuito
#define RN 10000.f            // resistência nominal do termorresistor
#define T1 (273.15 + 25)      // temperatura ambiente
#define ZA 273.15             // valor do zero absoluto (escala Kelvin)
#define B 3950.f              // constante

// Obtenção da voltagem analógica através do seu valor ADC
#define Voltage(adcVal) (float) adcVal/4095 * VMAX 

// Obtenção da resistência do termorresistor, usando divisor de tensão
#define RT(Voltage) ( VMAX/(VMAX-Voltage) - 1 ) * RN

/* Obtenção da temperatura no termorresistor através de:
*   Rt: resistência do termorresistor
*   Rn: resistência nominal do termorresistor 
*   T1: temperatura mínima (ambiente)
*   B: constante
*/
#define T2(Rt) 1/( 1/T1 + log(Rt/RN)/B )

// Obtenção da temperatura em graus Kelvin em função a temperatura em graus Celsius
#define tempC(tempK) tempK - ZA


void setup() {
  // Configuração da velocidade do terminal
  Serial.begin(115200);
}

void loop() {

  // obtenção do nível ADC da tensão no termostato
  int adcVal = analogRead(ANALOG_PIN_IN);

  // Obtenção da tensão no termostato através do nível ADC
  double voltage = Voltage(adcVal);

  // Obtenção da resistência do termostato através de sua tensão
  double rt = RT(voltage);

  // Obtenção da temperatura através da fórmula de var. da res. em relação a var. de temp. 
  double t2 = T2(rt);

  // Impressão dos dados
  Serial.printf("ADC = %d ; Vt = %.2f V ; T = %.2f C \n", adcVal, voltage, tempC(t2));
  delay(1000);

}


  