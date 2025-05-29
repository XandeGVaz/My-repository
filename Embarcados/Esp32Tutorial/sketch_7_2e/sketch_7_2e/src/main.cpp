#include <Arduino.h>

// Comunicação Serial (UART - Transmissão/Recepção Assícrona e Universal)

// Variáveis globais
String inputString = "";    // string de entrada
int stringComplet = 0; // flag de indicação dp término da entrada


void setup() {

  // Inicia comunicação serial com taxa de transmissão 115200
  Serial.begin(115200);
  
  // Mensagem de início do programa
  Serial.println(String("Inicialização da ESP 32 completa \n") +
                String("Insira caracteres e quando terminador \n"));

}

void loop() {

  char inChar;

  /* Serial.avaliable()
  * ->Saída: número de bytes disponíveis para serem lidos da porta serial
  * (esses são dados que já chegaram e foram armazenados no buffer do serial de recepção)
  */
  if(Serial.available()){ // se houver dados para leitura no serial (pela esp32), a mesma lê esses dados

    // Entrada do caractere via munitor serial
    inChar = Serial.read();
    
    // Adiciona caractere lido à string
    inputString += inChar;

    // Se a string estiver completa, termina a leitura
    if(inChar == '\n')
      stringComplet = 1;
  }

  if(stringComplet){

    // Mostra string digitada no monitor serial
    Serial.printf("input string: %s \n",inputString);
    
    // Reseta variáveis para digitação de nova string
    inputString = "";
    stringComplet = 0;
  }

}

