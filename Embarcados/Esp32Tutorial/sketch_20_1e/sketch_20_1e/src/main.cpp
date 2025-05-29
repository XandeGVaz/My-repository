#include <Arduino.h>
#include <BluetoothSerial.h> // bluetooth clássico

// Objeto da comunicação BT serial
BluetoothSerial SerialBT;

void setup() {
  // Configuração do monitor serial
  Serial.begin(115200);

  // Configuração do monitor bluetooth
  SerialBT.begin("ESP32_TEST"/*local name*/, false/*se é master*/);

  // Mensagem inicial
  Serial.println("\n Device started, now you can pair it with bluetooth!");

}

void loop() {

  // Se houver conteúdo transmitido pelo munitor serial, escrevemos no BT serial
  if(Serial.available()/*Verifica se há bits no buffer do monitor serial*/){
    SerialBT.write(Serial.read());
  }

  // Se houver conteúdo transmitido pelo BT serial, escrevemos no munitor serial
  if(SerialBT.available()/*Verifica se há bits no buffer do bluetooth serial*/){
    Serial.write(SerialBT.read());
  }

  // Delay entre verificações
  delay(20);

}

