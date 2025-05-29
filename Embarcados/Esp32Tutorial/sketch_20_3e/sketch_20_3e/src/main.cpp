#include <Arduino.h>
#include <BluetoothSerial.h>
#include <string.h>

// Defines
#define PIN_LED 2

// Variáveis globais
BluetoothSerial SerialBT; // objeto da comunicação bluetooth serial
char buffer[20];          // buffer de entrada do munitor serial
static int count;         // contador do número de caracteres de entrada no monitor


void setup() {
  // Configuração do monitor serial
  Serial.begin(115200);

  // Configuração do pino do LED
  pinMode(PIN_LED, OUTPUT);

  // Configuração do Bluetooth
  SerialBT.begin("ESP32_BLINK");

  // Mensagem de aviso 
  Serial.println("\nThe device started, now you can pair it with bluetooth");
}

void loop() {
  // Enquanto houver entrada de dados no canal bluetooth
  while(SerialBT.available()){
    // lemos os dadios, gravando-os em um buffer
    buffer[count] = SerialBT.read();
    count++;
  }
  
  // Caso tenham sido lidos dados
  if(count > 0){
    // Impressão das informações no monitor serial
    Serial.print(buffer);
    
    // Se o comando for de acendimento do LED
    if(strncmp(buffer, "led on", 6) == 0)
      digitalWrite(PIN_LED, HIGH);
    
    // Se o comando for de desativação do LED
    if(strncmp(buffer, "led off", 7) == 0)
      digitalWrite(PIN_LED, LOW);
  
    // Reset do contador
    count = 0;

    // "Limpeza" do buffer
    memset(buffer, 0, 20);
  }

  // Delay entre verificações para evitar erros
  delay(20);

}