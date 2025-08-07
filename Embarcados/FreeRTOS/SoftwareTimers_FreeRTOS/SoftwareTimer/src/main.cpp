/*
  * Exercício de utilização de timers autoreload e onse shot 
  * Implementar e criar sistema que avisa pelo acendimento de um led que a leitura adc será feita após acionar botão
  * Nesse caso, os Timers estão sendo usados para SINCRONIZAÇÂO de tarefas
*/

/* Biblioteca Arduino*/
#include <Arduino.h>

/* Uso da API do freeRTOS*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

/* Defines*/
#define LED_PIN 12
#define PONT_PIN 13
#define BUTTON_PIN 4

/* Prototypes das tasks */
void vTaskADC(void *pvParameters);
void vTaskButton(void *pvParameters);

/* Prototypes dos tratadores de interrupção e callbacks de timer*/
void handleISRButton();
void callbackTimer1(TimerHandle_t xTimer);
void callbackTimer2(TimerHandle_t xTimer);

/* Handles das tasks*/
TaskHandle_t xHandleTaskADC = NULL;

/* Handles de timers*/
TimerHandle_t xHandleTimer1 = NULL;
TimerHandle_t xHandleTimer2 = NULL;

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

  // Criação do timmer com autoreload
  xHandleTimer1 = xTimerCreate("TIMER1", pdMS_TO_TICKS(1000), pdTRUE, 0, callbackTimer1);
  if(xHandleTimer1 == NULL){
    Serial.println("Erro na criação do timer 1");
    while(1);
  }

  // Criação do timer one shot
  xHandleTimer2 = xTimerCreate("TIMER2", pdMS_TO_TICKS(10000), pdFALSE, 0, callbackTimer2);
  if(xHandleTimer2 == NULL){
    Serial.println("Erro na criação do timer 2");
    while(1);
  }

  // Criação de interrupções
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleISRButton, FALLING);

  // Criação das tasks
  if(xTaskCreate(vTaskADC, "TASK_ADC", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xHandleTaskADC) != pdPASS){
    Serial.println("Falha na criação da TASK1");
    while(1);
  }

  // Suspensão da Task1
  vTaskSuspend(xHandleTaskADC);
}

void loop() {
  vTaskDelete(NULL);
}

/* Definição dos tratadores de interrupção e callbacks de timer*/
void handleISRButton(){

  // Inicia Timer 2
  xTimerStartFromISR(xHandleTimer1, NULL);
  xTimerStartFromISR(xHandleTimer2, NULL);
}

void callbackTimer1(TimerHandle_t xTimer){

  // Inverte estado do led
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void callbackTimer2(TimerHandle_t xTimer){
  // Para o timer 1 ( led para de piscar)
  xTimerStop(xHandleTimer1, portMAX_DELAY);
  digitalWrite(LED_PIN, LOW);

  // Leitura ADC é feita
  vTaskResume(xHandleTaskADC);
}


/* Definição das Tasks*/
void vTaskADC(void *pvParameters){
  
  // Variável de armazenamento do valor recebido da fila
  int adcVal = 0;
  
  while(1){
    // Estando com o semáforo, faz leitura adc do potenciômetro
    Serial.println("TASK1: adcVal = " + String(analogRead(PONT_PIN)));

    // Task entra em suspensão
    vTaskSuspend(NULL);
  }
}