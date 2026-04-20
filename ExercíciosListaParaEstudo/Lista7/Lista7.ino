const int bt1 = 2; // ativa modo efeito
const int bt2 = 3; // desativa

const int led1 = 4;
const int led2 = 5;
const int led3 = 6;
const int led4 = 7;

bool modo = false; // false = desligado | true = efeito

// debounce bt1
bool ult1 = HIGH, est1 = HIGH;
unsigned long t1 = 0;

// debounce bt2
bool ult2 = HIGH, est2 = HIGH;
unsigned long t2 = 0;

const unsigned long debounce = 50;

// millis do efeito
unsigned long tempo = 0;
const unsigned long intervalo = 300;

bool fase = false; // alterna entre os pares

void setup() {
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  // ===== BOTÃO 1 (ativa modo) =====
  bool l1 = digitalRead(bt1);

  if (l1 != ult1) t1 = millis();

  if ((millis() - t1) > debounce) {
    if (l1 != est1) {
      est1 = l1;

      if (est1 == LOW) {
        modo = true; // ativa efeito
      }
    }
  }

  ult1 = l1;

  // ===== BOTÃO 2 (desativa modo) =====
  bool l2 = digitalRead(bt2);

  if (l2 != ult2) t2 = millis();

  if ((millis() - t2) > debounce) {
    if (l2 != est2) {
      est2 = l2;

      if (est2 == LOW) {
        modo = false; // desativa efeito

        // apaga tudo
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
      }
    }
  }

  ult2 = l2;

  // ===== MODO EFEITO =====
  if (modo) {
    if (millis() - tempo >= intervalo) {
      tempo = millis();

      fase = !fase; // alterna

      if (fase) {
        // LED1 + LED3
        digitalWrite(led1, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led4, LOW);
      } else {
        // LED2 + LED4
        digitalWrite(led2, HIGH);
        digitalWrite(led4, HIGH);
        digitalWrite(led1, LOW);
        digitalWrite(led3, LOW);
      }
    }
  }
}