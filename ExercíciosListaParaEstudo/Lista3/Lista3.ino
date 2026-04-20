
const int bt = 2;
const int led = 13;

bool leitura;
bool ultimo = HIGH;
bool estadoEstavel = HIGH;

bool estadoLed = false;

unsigned long tempo = 0;
const unsigned long debounce = 50;

void setup() {
  pinMode(bt, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  leitura = digitalRead(bt);

  // detecta mudança no botão
  if (leitura != ultimo) {
    tempo = millis();
  }

  // verifica debounce
  if ((millis() - tempo) > debounce) {

    // mudou de forma estável?
    if (leitura != estadoEstavel) {
      estadoEstavel = leitura;

      // detecta clique (HIGH -> LOW)
      if (estadoEstavel == LOW) {
        estadoLed = !estadoLed; // alterna LED
      }
    }
  }

  digitalWrite(led, estadoLed);

  ultimo = leitura;
}