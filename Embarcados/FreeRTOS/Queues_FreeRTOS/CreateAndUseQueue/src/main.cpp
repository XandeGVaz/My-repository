/*
  * Exercício de utilização de queues
  * Implementar e criar diferentes queues e verificar seu funcionamento
*/

/* Biblioteca Arduino*/
#include <Arduino.h>

/* Uso da API do freeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

/* Defines*/
#define LED_PIN 12

/* Prototypes das tasks */
void vTask1Code(void *pvParameters);
void vTask2Code(void *pvParameters);

/* Handles das tasks*/
TaskHandle_t xHandleTask1 = NULL;
TaskHandle_t xHandleTask2 = NULL;

/* Handle de fila*/
QueueHandle_t xHandleQueue = NULL;

void setup() {

  // Configuração do monitor serial
  Serial.begin(115200);

  // Configuração do pino de LED
  pinMode(LED_PIN, OUTPUT);
  
  // Criação da fila
  xHandleQueue = xQueueCreate(10, sizeof(int));

  // Criação das tasks
  if(xTaskCreate(vTask1Code, "TASK!", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xHandleTask1) != pdPASS){
    Serial.println("Falha na criação da TASK1");
    while(1);
  }
  if(xTaskCreate(vTask2Code, "TASK2", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xHandleTask2) != pdPASS){
    Serial.println("Falha na criação da TASK2");
    while(1);
  }
}

void loop() {

  // Acendimento de LED
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  vTaskDelay(pdMS_TO_TICKS(1000));
}

/* Definição das Tasks*/
void vTask1Code(void *pvParameters){
  
  int cont = 0;

  while(1){

    // Se o contador for menor que 10, enviamos o valor de contador para a fila e incrementamos o contador
    if(cont < 10){
      xQueueSend(xHandleQueue, &cont, portMAX_DELAY);
      cont++;
    }
    
    // Se o contador for maior ou igual a 10, reiniciamos o contador
    else{
      cont = 0;
      vTaskDelay(pdMS_TO_TICKS(5000));
    }

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void vTask2Code(void *pvParameters){
  int valorRecebido = 0;

  while(1){
    
    // Tentativa de receber valor da fila por 1 segundo
    if(xQueueReceive(xHandleQueue, &valorRecebido, pdMS_TO_TICKS(1000)) == pdTRUE){
      // Caso o valor seja recebido, imprimimos na tela
      Serial.println("Valor recebido da fila: " + String(valorRecebido));
    }

    // Caso o contrário (timeout) fila vazia por mais de 1 segundo
    else{
      Serial.println("TIMEOUT");
    }
  }
}
