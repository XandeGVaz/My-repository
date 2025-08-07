/*
  * Exercício de passagem de parâmetros de uma task
  * Implementar e criar diferentes tasks e verificar seu funcionamento
*/

/* Biblioteca de funções do Arduino framework*/
#include <Arduino.h>

/*Bibliotecas do FreeRTOS necessárias*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/* Estado Inicial do contador */
#define INITIAL_COUNTER 4

/* Configuração de pinos*/
typedef struct {
  uint8_t numberPin;
  uint8_t initialState;
}pin_t;

/* Handles das tasks*/
TaskHandle_t handleTask1 = NULL;
TaskHandle_t handleTask2 = NULL;

/* Protótipos das tasks */
void vTask1Code(void *pvParameters);
void vTask2Code(void *pvParameters);

void setup() {

  /* Pino do LED*/
  pin_t* ledPin = new pin_t;
  *ledPin = {.numberPin = 12, .initialState = LOW};

  /* Iniciação do monitor serial*/
  Serial.begin(115200);

  /* Criação das Tasks para serem executadas em cores diferentes (a esp32 possui dois cores)*/
  xTaskCreatePinnedToCore(vTask1Code, "TASK1", configMINIMAL_STACK_SIZE, (void*)(ledPin), 1, &handleTask1, APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTask2Code, "TASK2", configMINIMAL_STACK_SIZE + 1024, (void*)INITIAL_COUNTER, configMAX_PRIORITIES - 1, &handleTask2, PRO_CPU_NUM);
}

void loop() {
}

/* Definições dos códigos de implementação das tasks */
void vTask1Code(void *pvParameters){

  // Recepção de parâmetros utilizando endereço de dados sobre o pino alocados dinamicamente
  pin_t* ledPin = (pin_t*)(pvParameters);

  
  // Configura pino para saída
  pinMode(ledPin->numberPin, OUTPUT);
  digitalWrite(ledPin->numberPin, ledPin->initialState);
  
  while(1){
    /* Troca estado do LED*/
    digitalWrite(ledPin->numberPin, !digitalRead(ledPin->numberPin));
    
    /* Task bloqueada por 200 ms em ticks */
    vTaskDelay(pdMS_TO_TICKS(200)); 
  }
}

void vTask2Code(void *pvParameters){

  // Recepção do parâmetro utilizando o valor do próprio endereço (pvParameter = INITIAL_COUNTER)e convertendo para inteiro
  int cont = (int)pvParameters;
  
  while(1){

    // Imprime contador na tela e quantidade de bytes da stack utilizados
    Serial.println("Contador: " + String(cont++) + " , Stack Task2: " + String(uxTaskGetStackHighWaterMark(NULL)));

    // Suspensão da Task
    if(cont == 10){
      Serial.println("Suspendendo a Task1");
      vTaskSuspend(handleTask1);
    }

    // Reinício da Task
    if(cont == 15){
      Serial.println("Reiniciando aTask1");
      vTaskResume(handleTask1);
    }

    // Deleta a Task
    if(cont == 20){
      Serial.println("Deletando a Task1");
      vTaskDelete(handleTask1);
    }

    /* Task bloqueada por 1000 ms em ticks*/
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}