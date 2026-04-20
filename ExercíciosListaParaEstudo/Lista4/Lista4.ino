const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;

int atual = 0;

unsigned long tempo = 0;
const unsigned long intervalo = 300;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  if (millis() - tempo >= intervalo) {
    tempo = millis();

    // apaga todos
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);

    // acende um por vez
    if (atual == 0) digitalWrite(led1, HIGH);
    if (atual == 1) digitalWrite(led2, HIGH);
    if (atual == 2) digitalWrite(led3, HIGH);
    if (atual == 3) digitalWrite(led4, HIGH);

    atual++;

    if (atual > 3) {
      atual = 0;
    }
  }
}