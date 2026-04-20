const int bt1 = 2; // muda direção
const int bt2 = 3; // start/pause

const int leds[] = {4, 5, 6, 7};

int atual = 0;
int direcao = 1; // 1 = direita | -1 = esquerda
bool rodando = true;

// debounce botão 1
bool ult1 = HIGH, est1 = HIGH;
unsigned long t1 = 0;

// debounce botão 2
bool ult2 = HIGH, est2 = HIGH;
unsigned long t2 = 0;

const unsigned long debounce = 50;

// millis da sequência
unsigned long tempo = 0;
const unsigned long intervalo = 300;

void setup() {
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {

  // ===== BOTÃO 1 (troca direção) =====
  bool l1 = digitalRead(bt1);

  if (l1 != ult1) t1 = millis();

  if ((millis() - t1) > debounce) {
    if (l1 != est1) {
      est1 = l1;

      if (est1 == LOW) {
        direcao = -direcao; // inverte direção
      }
    }
  }

  ult1 = l1;

  // ===== BOTÃO 2 (start/pause) =====
  bool l2 = digitalRead(bt2);

  if (l2 != ult2) t2 = millis();

  if ((millis() - t2) > debounce) {
    if (l2 != est2) {
      est2 = l2;

      if (est2 == LOW) {
        rodando = !rodando; // alterna
      }
    }
  }

  ult2 = l2;

  // ===== SEQUÊNCIA =====
  if (rodando) {
    if (millis() - tempo >= intervalo) {
      tempo = millis();

      // apaga todos
      for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], LOW);
      }

      // acende atual
      digitalWrite(leds[atual], HIGH);

      // atualiza posição
      atual += direcao;

      // controle de limites
      if (atual > 3) atual = 0;
      if (atual < 0) atual = 3;
    }
  }
}