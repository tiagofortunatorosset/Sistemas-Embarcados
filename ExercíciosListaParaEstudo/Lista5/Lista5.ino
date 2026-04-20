const int bt = 2;

const int led1 = 3; // bit 0 (LSB)
const int led2 = 4; // bit 1
const int led3 = 5; // bit 2
const int led4 = 6; // bit 3 (MSB)

int cont = 0;

bool leitura;
bool ultimo = HIGH;
bool estadoEstavel = HIGH;

unsigned long tempo = 0;
const unsigned long debounce = 50;

void setup() {
  pinMode(bt, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  leitura = digitalRead(bt);

  // detecta mudança
  if (leitura != ultimo) {
    tempo = millis();
  }

  // debounce
  if ((millis() - tempo) > debounce) {

    if (leitura != estadoEstavel) {
      estadoEstavel = leitura;

      // clique (HIGH -> LOW)
      if (estadoEstavel == LOW) {
        cont++;

        if (cont > 15) {
          cont = 0;
        }
      }
    }
  }

  ultimo = leitura;

  // mostra em binário nos LEDs
  digitalWrite(led1, cont & 1);        // bit 0
  digitalWrite(led2, (cont >> 1) & 1); // bit 1
  digitalWrite(led3, (cont >> 2) & 1); // bit 2
  digitalWrite(led4, (cont >> 3) & 1); // bit 3
}