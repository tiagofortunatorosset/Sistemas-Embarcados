const int led = 13;

unsigned long tempoAnterior = 0;
const unsigned long intervalo = 500; // 500 ms

bool estadoLed = false;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  unsigned long tempoAtual = millis();

  // verifica se passou 500 ms
  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;      // atualiza o tempo
    estadoLed = !estadoLed;          // inverte o estado
    digitalWrite(led, estadoLed);    // aplica no LED
  }
}