/*
  * Exercício de utilização de queues com interrupção (obs: não há filtro para evitar boucing do botão de ISR)
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
#define BUTTON_PIN 4

/* Prototypes das tasks */
void vTask1Code(void *pvParameters);

/* Prototypes dos tratadores de interrupção*/
void handleISRButton();

/* Handles das tasks*/
TaskHandle_t xHandleTask1 = NULL;

/* Handle de fila*/
QueueHandle_t xHandleQueue = NULL;

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

  // Criação da fila
  xHandleQueue = xQueueCreate(30, sizeof(int));

  // Criação de interrupções
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleISRButton, FALLING);

  // Criação das tasks
  if(xTaskCreate(vTask1Code, "TASK!", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &xHandleTask1) != pdPASS){
    Serial.println("Falha na criação da TASK1");
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

  // Variável de armazenamento do valor recebido da fila
  int valorRecebido = 0;

  while(1){

    // Espera pela recepção do valor da fila
    xQueueReceive(xHandleQueue, &valorRecebido, portMAX_DELAY);
    Serial.println("Apertos de botao: " + String(valorRecebido));
  }
}

/* Definição dos tratadores de interrupção*/
void handleISRButton(){

  // Variável estática de implementação
  static int cont;

  // Incrementação 
  cont++;

  // Envia contador para a fila
  xQueueSendFromISR(xHandleQueue, &cont, NULL);
}