#include <Arduino.h>
#include <WiFi.h>

// Informações da rede WiFi transmitida pelo roteador
const char *ssidAP =  "ESP_WiFi"; // nome da rede
const char *passwordAP =  "12345678";     // senha

// WiFi IP´s
IPAddress localIP (192,168,1,100);
IPAddress gateway (192,168,1,10);
IPAddress subnet (255,255,255,0);


void setup() {

  // Configuração do monitor serial
  Serial.begin(115200);

  // Delay entre configuração e utilização do monitor
  delay(1000);

  // Configuração do wifi foi iniciada
  Serial.println("Setting soft-AP configuration...");

  // Término da conexão anterior
  WiFi.disconnect();
  
  // Modo da conexão WiFi
  WiFi.mode(WIFI_AP);
  
  // Configuração da conexão WiFi
  WiFi.begin(ssidAP, passwordAP);

  // Configuração do WiFi no modo AP
  Serial.println("Setting soft-Ap ...");
  Serial.println(WiFi.softAPConfig(localIP, gateway, subnet) ? "Ready!" : "Failed!");

  // Término da configuração
  bool result = WiFi.softAP(ssidAP, passwordAP);
  
  // Caso bem sucedida, imprime IP e MAC ADDR da conexão configurada (com o ESP como posto de transmissão)
  if(result){
    Serial.println("Success of setting");
    Serial.println(String("Spft-AP IP: ") + WiFi.softAPIP().toString());
    Serial.println(String("MAC address: ") + WiFi.softAPmacAddress());
  }

  
  else{
    Serial.println("Failed of setting");
  }

  Serial.println("Setup ended");
}

void loop() {
//
}

