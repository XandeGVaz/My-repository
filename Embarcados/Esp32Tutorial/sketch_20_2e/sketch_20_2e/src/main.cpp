#include <Arduino.h>
#include <string>

// BLE (bluetooth de baixa energia)
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// UUID sercices
#define SERVICE_UUID            "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX  "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX  "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// Variáveis globais
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
uint8_t txValue = 0;
long lastMsg = 0;
String rxload="Test\n";

// Classe para retorno da ativação/desativação do sistema
class MyServerCallbacks: public BLEServerCallbacks{
  
  void onConnect(BLEServer *pServer){
    deviceConnected = true;
  }

  void onDisconnect(BLEServer *pServer){
    deviceConnected = false;
  }

};

// Classe com retorno da características de recepção de dados pela ESP (Write para o Master)
class MyCallbacks: public BLECharacteristicCallbacks{
  void onWrite(BLECharacteristic *pCharacteristic){
    std::string rxValue = pCharacteristic->getValue();
    
    if(rxValue.length() > 0){
      
      rxload = "";
      
      for(int i = 0; i < rxValue.length(); i++){
        rxload += (char)rxValue[i]; 
      }
    }

  }
};

void setupBLE(String BLEName){

  // Obtemos string padrão de C do nome do server
  const char *ble_name = BLEName.c_str();

  // Criação do dispositivo BLE
  BLEDevice::init(ble_name);

  // Criação do server do BLE
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Criação do serviço BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Criação de primeira característica do serviço BLE (TRANSMISSÃO DE DADOS - ESP para Master)
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX/*ID da característica*/, BLECharacteristic::PROPERTY_NOTIFY/*propriedade da característica do serviço*/);

  // Criação de descritor para a característica
  pCharacteristic->addDescriptor(new BLE2902());

  // Criação da segunda característica do serviço BLE (RECEPÇÃO DE DADOS - ESP recebe do MAster)
  BLECharacteristic * pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX/*ID da característica*/, BLECharacteristic::PROPERTY_WRITE/*propriedade da característica do serviço*/);
  
  // Retorno da característica (nesse caso como é de recepção, possui como retorno o dado recebido)
  pCharacteristic->setCallbacks(new MyCallbacks);

  // Inicia serviço
  pService->start();

  // Cria anúncio do serviço (adverte a existência do server)
  pServer->getAdvertising()->start();

  // Notificação Serial
  Serial.println("Waiting a client connection to notify");

}

void setup() {

  // Configura monitor serial
  Serial.begin(9600);
  
  // Configura BLE
  setupBLE("ESP32_BLE");
}

void loop() {

  // Obtém tempo decorrido deste o início do programa
  long now = millis();

  // Se o tempo for válido
  if(now - lastMsg > 0){
    
    // Caso houve recepção de dados pela ESP (SLAVE)
    if(deviceConnected && rxload.length() > 0){
      Serial.println(rxload);
      rxload = "";
    }

    // Caso houve a escrita de dados paraa transfeência da ESP para o MASTER
    if(Serial.available() > 0){
      
      // Obtenção de dado do monitor serial
      String str = Serial.readString();

      // Transmissão do dado para o MASTER
      const char *value = str.c_str();
      pCharacteristic->setValue(value);
      pCharacteristic->notify(); // notifica dado ao MASTER
    }

    // Atualiza tempo de ocorrência da última mensagem
    lastMsg = now;
  }
}
