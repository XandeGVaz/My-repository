#include <Arduino.h>

// Pinos de conexão entre ESP32 e sonar 
#define TRIGGER_PIN 13
#define ECHO_PIN 14

// Parâmetros para medição de distância (d = Vsom * t / 2)
#define MAXDIST 700 // o sonar tem máxima distância possível de ser medida de 700cm
#define SOUND_VELOCITY 340 // velocidade do som é de 340 m/s
#define TIME_OUT MAXDIST/(SOUND_VELOCITY)*2000000 // tempo máximo (us) entre sinal enviado e recebido

/* Função responsável por obter a distância entre o sonar e o primeiro obstáculo
  -> Parâmetros: não possui
  -> Saída: distância em cm
*/
float getSonar(); 

void setup() {
  
  // Configuração do pino de acionamento do sonar 
  pinMode(TRIGGER_PIN, OUTPUT);

  // Configuração do pino de leitura do sonar
  pinMode(ECHO_PIN, INPUT);

  // Iniciação do monitor serial
  Serial.begin(115200);
}

void loop() {

  // Impressão de texto no monitor serial
  Serial.printf("Distance: %.2f cm\n", getSonar());
  
  // Uma medição por segundo
  delay(1000);
}

float getSonar(){
  
  // Acionamento do sonar (de acordo com manual -> um pulso de 10 us)
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Obtenção do tempo (em microssegundos) de percorrimento da onda do sonar
  //->Equivale ao tempo do pulso de entrada no ECHO_PIN (tempo em que ECHO permanece em nível alto)
  /* pulseIn
  *   -> Função responsável por medir (em us) o tempo em que um sinal de entrada em um pino permanece
  * em um determinado estado.
  */
  unsigned long timeSignal = pulseIn(ECHO_PIN, HIGH, TIME_OUT);

  // Retorno da distância entre o obstáculo e o sonar
  return timeSignal * SOUND_VELOCITY / 20000; 
}
