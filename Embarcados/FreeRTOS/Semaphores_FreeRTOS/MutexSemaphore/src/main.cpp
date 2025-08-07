/*
  * Exercício de utilização de semáforos de múltipla exclusão (mutex) 

  * O objetivo é poermitir que somente uma task (de duas tasks com diferentes prioridades) 
  *tenham aceso a uma funcionalidade específica (de impressão da task) por vez 

  * Nesse caso, os semáforos estão sendo usados para SINCRONIZAÇÂO de tarefas
*/

/* Biblioteca Arduino*/
#include <Arduino.h>

/* Uso da API do freeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

/* Defines*/
#define LED_PIN 12

/* Prototype de recurso de impressão*/
void vImprimeTask(char i);

/* Prototypes das tasks */
void vTaskA(void *pvParameters);
void vTaskB(void *pvParameters);


/* Handles das tasks*/
TaskHandle_t xHandleTaskA = NULL;
TaskHandle_t xHandleTaskB = NULL;

/* Handles de semáforos*/
SemaphoreHandle_t xHandleSemaphoreMutex = NULL;

void setup() {

  // Configuração do monitor serial
  Serial.begin(115200);

  // Configuração do pino de LED
  pinMode(LED_PIN, OUTPUT);

  // Criação ds semáforo mutex
  xHandleSemaphoreMutex = xSemaphoreCreateMutex();
  if(xHandleSemaphoreMutex == NULL){
    Serial.println("Erro na criação do semaforo 1");
    while(1);
  }

  // Criação das tasks
  if(xTaskCreate(vTaskA, "TASK A", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xHandleTaskA) != pdPASS){
    Serial.println("Falha na criação da TASK1");
    while(1);
  }
  if(xTaskCreate(vTaskB, "TASK B", configMINIMAL_STACK_SIZE + 1024, NULL, 2, &xHandleTaskB) != pdPASS){
    Serial.println("Falha na criação da TASK1");
    while(1);
  }
}

void loop() {

  // Acendimento de LED
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  vTaskDelay(pdMS_TO_TICKS(1000));
}

/* Definição de função auxiliar*/
void vImprimeTask(char i){

  // Task bloqueada, aguardando pela liberação do mutex
  xSemaphoreTake(xHandleSemaphoreMutex, portMAX_DELAY);

  // Impressão da task que está utilizando o recurso de impressão
  Serial.println("Turn: Task " + String(i));

  // Devolução do semáfoto, task passa novamente para o estado bloqueada
  xSemaphoreGive(xHandleSemaphoreMutex);

  /* 
    * Caso não haja esse delay (pode ser menor que 500ms) ocorre STARVATION
    * Task é novamente executada e, tendo maior prioridade que as demais, as demais não são executadas
    * Por fim, o delay garante a execução das demais tasks com menos prioridade e que utilizam do
    *recurso gerenciado pelo mutex
  */
  vTaskDelay(pdMS_TO_TICKS(500));
}

/* Definição das Tasks*/
void vTaskA(void *pvParameters){
  
  char task = 'A';
  
  while(1){

    // Obtenção do semáforo desbloqueado, imprime-se a task
    vImprimeTask(task);

  }
}

void vTaskB(void *pvParameters){
   
  char task = 'B';
  
  while(1){

    // Obtenção do semáforo desbloqueado, imprime-se a task
    vImprimeTask(task);
    
  }
}