const int bt1 = 2; // incrementa
const int bt2 = 3; // decrementa

const int leds[] = {4, 5, 6, 7}; // LED1 a LED4

int cont = 0;

// debounce botão 1
bool ult1 = HIGH;
bool est1 = HIGH;
unsigned long t1 = 0;

// debounce botão 2
bool ult2 = HIGH;
bool est2 = HIGH;
unsigned long t2 = 0;

const unsigned long debounce = 50;

void setup() {
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // ===== BOTÃO 1 (incrementa) =====
  bool leitura1 = digitalRead(bt1);

  if (leitura1 != ult1) {
    t1 = millis();
  }

  if ((millis() - t1) > debounce) {
    if (leitura1 != est1) {
      est1 = leitura1;

      if (est1 == LOW) {
        if (cont < 15) cont++; // não passa de 15
      }
    }
  }

  ult1 = leitura1;

  // ===== BOTÃO 2 (decrementa) =====
  bool leitura2 = digitalRead(bt2);

  if (leitura2 != ult2) {
    t2 = millis();
  }

  if ((millis() - t2) > debounce) {
    if (leitura2 != est2) {
      est2 = leitura2;

      if (est2 == LOW) {
        if (cont > 0) cont--; // não vai abaixo de 0
      }
    }
  }

  ult2 = leitura2;

  // ===== MOSTRA NOS LEDs =====
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], (cont >> i) & 1);
  }
}