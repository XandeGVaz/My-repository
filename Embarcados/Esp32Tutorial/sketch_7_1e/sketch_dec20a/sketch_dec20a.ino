
// put function declarations here:
int myFunction(int, int);

void setup() {

  // Iniciação da comunicação serial
  Serial.begin(115200);

  // Print de inicialização
  Serial.printf("Inicializacao da ESP 32!");  
}

void loop() {

  // Print de tempo de funcionamento do programa
  Serial.printf("O programa está funcionando a %.1f s\n", millis()/1000.0f);
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}