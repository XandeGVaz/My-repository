/*
  * Exercício de utilização de semáforos binário e semáforo contador
  * Implementar e criar diferentes semáforos e verificar seu funcionamento
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
#define PONT_PIN 13
#define BUTTON_PIN 4

/* Prototypes das tasks */
void vTaskADC(void *pvParameters);
void vTaskButton(void *pvParameters);

/* Prototypes dos tratadores de interrupção*/
void handleISRButton();

/* Handles das tasks*/
TaskHandle_t xHandleTaskADC = NULL;
TaskHandle_t xHandleTaskButton = NULL;

/* Handles de semáforos*/
SemaphoreHandle_t xHandleSemaphoreBinary = NULL;
SemaphoreHandle_t xHandleSemaphoreCounter = NULL;

void setup() {

  // Configuração do monitor serial
  Serial.begin(115200);

  // Configuração do pino de LED
  pinMode(LED_PIN, OUTPUT);

  /* 
    * Configuração do pino de entrada do botão, com resistor de pull up (da própria placa)
    * Necessária para possibilitar a interrupção
  */
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Configuração do pino de ADC
  pinMode(PONT_PIN, INPUT);

  // Criação ds semáforo binário
  xHandleSemaphoreBinary = xSemaphoreCreateBinary();
  if(xHandleSemaphoreBinary == NULL){
    Serial.println("Erro na criação do semaforo 1");
    while(1);
  }

  // Criação de semáforo contador
  xHandleSemaphoreCounter = xSemaphoreCreateCounting(10, 0);
  if(xHandleSemaphoreCounter == NULL){
    Serial.println("Erro na criação do semaforo 2");
    while(1); 
  }

  // Criação de interrupções
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleISRButton, FALLING);

  // Criação das tasks
  if(xTaskCreate(vTaskADC, "TASK_ADC", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xHandleTaskADC) != pdPASS){
    Serial.println("Falha na criação da TASK1");
    while(1);
  }
  if(xTaskCreate(vTaskButton, "TASK_BUTTON", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xHandleTaskButton) != pdPASS){
    Serial.println("Falha na criação da TASK1");
    while(1);
  }
}

void loop() {

  // Acendimento de LED
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  vTaskDelay(pdMS_TO_TICKS(1000));

  // Libera Semáforo
  xSemaphoreGive(xHandleSemaphoreBinary);
}

/* Definição dos tratadores de interrupção*/
void handleISRButton(){

  // Verificação de de ativação de Task de maior prioridade
  BaseType_t xHigherPriorityTaskWoken = pdTRUE;

  // Fornece semáforo
  xSemaphoreGiveFromISR(xHandleSemaphoreCounter, &xHigherPriorityTaskWoken);
  
  if(xHigherPriorityTaskWoken == pdTRUE){
    /* 
      * Caso haja uma task de maior prioridade, força sua execução pelo escalonador
      * Caso isso não seja feito, escalonador demora cerca de um systick para reconhecer a task de maior prioridade e trocar de contexto
    */
    portYIELD_FROM_ISR();
  }
}

/* Definição das Tasks*/

void vTaskADC(void *pvParameters){
  
  // Variável de armazenamento do valor recebido da fila
  int adcVal = 0;
  
  while(1){
    // Espera (bloqueada) pela disponibilidade do semnáforo 1
    xSemaphoreTake(xHandleSemaphoreBinary, portMAX_DELAY);

    // Estando com o semáforo, faz leitura adc do potenciômetro
    Serial.println("TASK1: adcVal = " + String(analogRead(PONT_PIN)));
  }
}

void vTaskButton(void *pvParameters){

  // Variável de armazenamento do valor recebido da fila
  int cont = 0;

  while(1){
    // Espera (bloqueada) pela disponibilidade do semáforo 2
    xSemaphoreTake(xHandleSemaphoreCounter, portMAX_DELAY);

    // Estando com o semáforo, incrementa acionamentos do botão
    Serial.println("TASK2: butonCounter = " + String(cont++));
    
    // Delay de tratamento da liberação do semáforo contador
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}