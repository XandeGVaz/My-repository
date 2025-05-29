#include <Arduino.h>

// Vetor de configuração de pinos
int xyzInput [] = {13, 12, 14};
int xyzOutput [] = {15, 2, 0};

// Ajuste para as luzes ligarem quando houver movimento dos cursores
#define adjustment(val) (val > 4000 ) ? val : ( (val < 100 ) ? 100 : 0 )

void setup() {
  
  // Configuração da taxa de transmissão do monitor serial
  Serial.begin(115200);

  // Configuração e conexão dos canais pwm com os pinos dos leds
  for(int i = 0; i<3; i++)
    ledcAttachChannel(xyzOutput[i], 1000, 12, i);
}

void loop() {
  
  // Leitura do adc dos pinos de entrada
  int adcX = analogRead(xyzInput[0]);
  int adcY = analogRead(xyzInput[1]);
  int adcZ = analogRead(xyzInput[2]);

  // Valores pwm para acendimento de leds
  int pwmX = adjustment(adcX); // ajuste
  int pwmY = adjustment(adcY); // ajuste
  int pwmZ = map(adcZ, 0, 4095, 4095, 0); // inversão de sinal

  // Saída analógica (modulada com pwm) nos pinos dos leds 
  ledcWrite(xyzOutput[0], pwmX);
  ledcWrite(xyzOutput[1], pwmY);
  ledcWrite(xyzOutput[2], pwmZ);

  // Exposição de valores no monitor serial
  Serial.printf("X,Y,Z = (%d, %d, %d)\n", adcX,adcY,adcZ);

  // Intervalo entre medições (0.5 segundos)
  delay(50);

}
