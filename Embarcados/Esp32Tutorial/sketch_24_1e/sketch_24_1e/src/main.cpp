#include <Arduino.h>
#include <WiFi.h>

// Informações da rede WiFi transmitida pelo roteador
const char *ssidRounter =  "Usa 3G folgado_2.4GHZ"; // nome da rede
const char *passwordRounter =  "soentrabonito";     // senha

void setup() {

  // Configuração do monitor serial
  Serial.begin(115200);

  // Delay entre configuração e utilização do monitor
  delay(100);

  // Aviso de que a configuração do wifi foi iniciada
  Serial.println("WiFi setup started");

  // Configuração da conexão WiFi
  WiFi.begin(ssidRounter, passwordRounter);

  // Enquanto não conectado com o rounter, imprime "."
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.printf(".");
  }

  // Configuração da conexão terminada + impressão do IP
  Serial.print("\nConnected, with IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("End setup");
}

void loop() {
//
}

