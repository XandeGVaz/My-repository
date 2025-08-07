/*
  * Exercício de utilização de EventGroups

  * O objetivo é usar event groups para ativar tasks (tirar do estado de bloqueio)

  * Nesse caso, os event groups estão sendo usados para SINCRONIZAÇÂO de tarefas
*/

/* Biblioteca Arduino*/
#include <Arduino.h>

/* Uso da API do freeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <freertos/event_groups.h>

/* Defines*/
#define LED_PIN 12
#define BIT_0 (1<<0)
#define BIT_1 (1<<1)

/* Prototypes das tasks */
void vTaskA(void *pvParameters);
void vTaskB(void *pvParameters);

/* Prototype de callback do timer*/
void callbackTimer(TimerHandle_t xTimer);

/* Handles das tasks*/
TaskHandle_t xHandleTaskA = NULL;
TaskHandle_t xHandleTaskB = NULL;

/* Handle do eventGroup*/
EventGroupHandle_t xHandleEventGroup = NULL;

/* Handle do timer*/
TimerHandle_t xHandleTimer = NULL;

void setup() {

  // Configuração do monitor serial
  Serial.begin(115200);

  // Configuração do pino de LED
  pinMode(LED_PIN, OUTPUT);

  // Criação do timer
  xHandleTimer = xTimerCreate("TIMER1", pdMS_TO_TICKS(2000), pdTRUE, 0, callbackTimer);

  // Criação do event group
  xHandleEventGroup = xEventGroupCreate();

  // Criação das tasks
  if(xTaskCreate(vTaskA, "TASK A", configMINIMAL_STACK_SIZE + 1024, NULL, 2, &xHandleTaskA) != pdPASS){
    Serial.println("Falha na criação da TASK1");
    while(1);
  }
  if(xTaskCreate(vTaskB, "TASK B", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xHandleTaskB) != pdPASS){
    Serial.println("Falha na criação da TASK1");
    while(1);
  }

  // Inicia timer
  xTimerStart(xHandleTimer, portMAX_DELAY);
}

void loop() {

  // Acendimento de LED
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  vTaskDelay(pdMS_TO_TICKS(1000));
}

/* Definição do callback timer*/
void callbackTimer(TimerHandle_t xTimer){

  // Contador de execuções
  static int count = 0;

  // Por dois segundos executa task A
  if(count == 0){
    xEventGroupSetBitsFromISR(xHandleEventGroup, BIT_0, NULL);
    count++;
    return;
  }

  // Por dois segundos executa task B
  if(count == 1){
    xEventGroupSetBitsFromISR(xHandleEventGroup, BIT_1, NULL);
    count++;
    return;
  }

  // Por outros dois segundos, executa tasks A e B
  if(count == 2){
    xEventGroupSetBitsFromISR(xHandleEventGroup, (BIT_0|BIT_1), NULL);
    count = 0;
    return;
  }
}

/* Definição das Tasks*/
void vTaskA(void *pvParameters){
  
  // Bits de evento que serão recebidos
  EventBits_t bits;
  
  while(1){

    // Aguarda bloqueada pela setagem do event bit 0
    bits = xEventGroupWaitBits(xHandleEventGroup, BIT_0, pdTRUE, pdTRUE, portMAX_DELAY);

    // Caso o event bit tenha sido alterado imprime-se a task
    Serial.println("Task A - BitsEventGroup: " + String(bits) );
  }
}

void vTaskB(void *pvParameters){
   
  // Bits de evento que serão recebidos
  EventBits_t bits;
  
  while(1){

    // Aguarda bloqueada pela setagem do event bit 0
    bits = xEventGroupWaitBits(xHandleEventGroup, BIT_1, pdTRUE, pdTRUE, portMAX_DELAY);

    // Caso o event bit tenha sido alterado imprime-se a task
    Serial.println("Task B - BitsEventGroup: " + String(bits) );
  }
}