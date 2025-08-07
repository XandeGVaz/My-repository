/*
  * Exercício de criação de tasks com FreeRTOS
  * Implementar e criar diferentes tasks e verificar seu funcionamento
*/

/* Biblioteca de funções do Arduino framework*/
#include <Arduino.h>

/*Bibliotecas do FreeRTOS necessárias*/
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/* COnfiguração de pinos*/
#define LED_PIN 12

/* Handles das tasks*/
TaskHandle_t handleTask1 = NULL;
TaskHandle_t handleTask2 = NULL;

/* Protótipos das tasks */
void vTask1Code(void *pvParameters);
void vTask2Code(void *pvParameters);


void setup() {

  /* Iniciação do monitor serial*/
  Serial.begin(115200);

  /* Criação das Tasks*/
  xTaskCreate(vTask1Code, "TASK1", configMINIMAL_STACK_SIZE, NULL, 1, &handleTask1);
  xTaskCreate(vTask2Code, "TASK2", configMINIMAL_STACK_SIZE + 1024, NULL, configMAX_PRIORITIES - 1, &handleTask2);
}

void loop() {
}

/* Definições dos códigos de implementação das tasks */
void vTask1Code(void *pvParameters){
  // Configura pino para saída
  pinMode(LED_PIN, OUTPUT);
  
  while(1){
    /* Troca estado do LED*/
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    
    /* Task bloqueada por 200 ms em ticks */
    vTaskDelay(pdMS_TO_TICKS(200)); 
  }
}

void vTask2Code(void *pvParameters){

  int cont = 0;
  
  while(1){
    // Imprime contador na tela
    Serial.printf("Contador: %d\n", cont);

    // Incrementa contador
    cont++;

    /* Task bloqueada por 1000 ms em ticks*/
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}