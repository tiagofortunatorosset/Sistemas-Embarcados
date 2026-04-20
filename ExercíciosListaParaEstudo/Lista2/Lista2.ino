const int bt = 2;
const int led = 13;

void setup() {
  pinMode(bt, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  int leitura = digitalRead(bt);

  if (leitura == LOW) {
    digitalWrite(led, HIGH); // botão pressiona LED liga
  } else {
    digitalWrite(led, LOW);  // botão solto LED desliga
  }
}