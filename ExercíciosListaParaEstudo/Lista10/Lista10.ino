const int bt0 = 2;  // botão que vale 0
const int bt1 = 3;  // botão que vale 1

const int leds[] = {8, 9, 10, 11};

int senha[4] = {1, 0, 1, 0};
int entrada[4];

int indice = 0;

unsigned long tempo = 0;
bool verificando = false;
bool erro = false;
bool sucesso = false;
int piscadas = 0;

void setup() {
  pinMode(bt0, INPUT_PULLUP);
  pinMode(bt1, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  unsigned long agora = millis();

  // --- leitura dos botões ---
  if (!verificando) {
    if (digitalRead(bt0) == LOW) {
      entrada[indice++] = 0;
      Serial.println("0");
      delay(200); // evita múltiplos cliques
    }

    if (digitalRead(bt1) == LOW) {
      entrada[indice++] = 1;
      Serial.println("1");
      delay(200);
    }

    // quando completar 4 bits
    if (indice == 4) {
      verificando = true;
      tempo = agora;

      sucesso = true;
      for (int i = 0; i < 4; i++) {
        if (entrada[i] != senha[i]) {
          sucesso = false;
        }
      }

      erro = !sucesso;
      piscadas = 0;
    }
  }

  // --- senha correta ---
  if (sucesso) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
    }

    if (agora - tempo >= 2000) {
      resetar();
    }
  }

  // --- senha errada (piscar rápido) ---
  if (erro) {
    if (agora - tempo >= 200) {
      tempo = agora;

      for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], !digitalRead(leds[i]));
      }

      piscadas++;

      if (piscadas >= 10) {
        resetar();
      }
    }
  }
}

// --- função para reiniciar ---
void resetar() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
    entrada[i] = 0;
  }

  indice = 0;
  verificando = false;
  erro = false;
  sucesso = false;
}