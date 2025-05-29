#include <Arduino.h>
#include <LiquidCrystal_I2C.h>  // biblioteca para administrar LCDs usando protocolo I2C
#include <Wire.h>               // biblioteca para estabelecer barramentos (conexões)

// Defines 
#define SDA 13
#define SCL 14 // I2C bus
/*
* lcd1602 que usa PCF8574T, endereço I2C é 0x27 
* lcd1602 que usa PCF8574AT, endereço I2c é 0x3F
*/
#define CI_ADDR1 0x27
#define CI_ADDR2 0x3F

// Objeto lcd
LiquidCrystal_I2C lcd (CI_ADDR1/*endereço*/, 16/*n colunas*/, 2/*n linhas*/);

// Declaração de funções
bool I2CAddrTest(byte addr);

void setup() {

  // Barramento de dados + controle
  Wire.begin(SDA, SCL); // necessário para o funcionamento da biblioteca LiquidCrystal_I2C 

  // Caso o endereço do CI não exista no lcd, então trocamos de endereço
  if(!I2CAddrTest(CI_ADDR1))
    lcd = LiquidCrystal_I2C(CI_ADDR2, 16, 2);

  // Iniciação do driver do LCD
  lcd.init();

  // Abre luz de fundo do LCD
  lcd.backlight();

  // Seta a posição de impressão no lcd no início da primeira linha
  lcd.setCursor(0,0);

  // Escrita no lcd
  lcd.print("Hello, World!");

}

void loop() {
  // Seta a posição de impressão no lcd no início da segunda linha
  lcd.setCursor(0,1);

  // Impressão de tempo de funcionamento do programa no lcd
  lcd.print("Counter: " + String(millis()/1000));

  // Delay de 1 segundo
  delay(1000);
}

// Função responssável por testar a conexão de um endereço (verificando se ele existe)
bool I2CAddrTest(byte addr){
  // Começa transmissão de barramento com o endereço passado por parâmetro
  Wire.beginTransmission(addr);
  
  // Se a transmissão ocorrer automaticamente, o endereço existe
  if(Wire.endTransmission() == 0);
    return true;
  
  // Caso contrário (demorou mais tempo para término da transmissão), o endereço não existe
  return false;
}