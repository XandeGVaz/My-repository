/*
  * Exercício de utilização de Task Notification no lugar de semáforos binário e contador 
  * Implementar e criar diferentes taskNotifications no lugar de semáforos
  * Nesse caso, as task notifications estão sendo usados para SINCRONIZAÇÂO de tarefas
*/

/* Biblioteca Arduino*/
#include <Arduino.h>

/* Uso da API do freeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

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

  // Criação de interrupções
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleISRButton, FALLING);

  // Criação das tasks
  if(xTaskCreate(vTaskADC, "TASK_ADC", configMINIMAL_STACK_SIZE + 1024, NULL, 2, &xHandleTaskADC) != pdPASS){
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
}

/* Definição dos tratadores de interrupção*/
void handleISRButton(){

  BaseType_t HighPriorityTaskWoken = pdTRUE;

  // Envio de Task Notifications
  vTaskNotifyGiveFromISR(xHandleTaskADC, &HighPriorityTaskWoken);
  if(HighPriorityTaskWoken == pdTRUE){
    portYIELD_FROM_ISR();
  }

  vTaskNotifyGiveFromISR(xHandleTaskButton, &HighPriorityTaskWoken);
  if(HighPriorityTaskWoken == pdTRUE){
    portYIELD_FROM_ISR();
  }

}

/* Definição das Tasks*/

void vTaskADC(void *pvParameters){
  
  // Variável de armazenamento do valor recebido da fila
  int adcVal = 0;
  
  while(1){
    // Espera (bloqueada) pelo envio da task notification, com o efeito de clear após o recebimento
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // Estando com o semáforo, faz leitura adc do potenciômetro
    Serial.println("TASK1: adcVal = " + String(analogRead(PONT_PIN)));

    // Evita mostrar vários valores devido ao efeito de baucing
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void vTaskButton(void *pvParameters){

  // Variável de armazenamento do valor recebido da fila
  int cont = 0;

  while(1){

    // Espera (bloqueada) pelo envio da task notification, com efeito de decremento após o recebimento
    cont = ulTaskNotifyTake(pdFAIL, portMAX_DELAY);

    // Estando com o semáforo, incrementa acionamentos do botão
    Serial.println("TASK2: butonCounter = " + String(cont));
    
    // Delay de tratamento da liberação do semáforo contador
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}