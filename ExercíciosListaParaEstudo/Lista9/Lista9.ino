// ===== BOTÕES =====
const int bt1 = 2; // representa LED1
const int bt2 = 3; // representa LED2 (2 cliques = LED3)

// ===== LEDS =====
const int led1 = 4;
const int led2 = 5;
const int led3 = 6;

// ===== SEQUÊNCIA =====
int seq[3] = {1, 3, 2}; // LED1 → LED3 → LED2
int entrada[3];         // resposta do usuário

int passo = 0;
bool mostrando = true;

// ===== millis =====
unsigned long tempo = 0;
const unsigned long intervalo = 500;

// ===== controle de clique =====
bool ult1 = HIGH, ult2 = HIGH;
unsigned long ultimoClique = 0;

int cliquesBt2 = 0;

void setup() {
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {

  // ===== MOSTRA SEQUÊNCIA =====
  if (mostrando) {
    if (millis() - tempo >= intervalo) {
      tempo = millis();

      // apaga tudo
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);

      // acende o LED da sequência
      if (seq[passo] == 1) digitalWrite(led1, HIGH);
      if (seq[passo] == 2) digitalWrite(led2, HIGH);
      if (seq[passo] == 3) digitalWrite(led3, HIGH);

      passo++;

      if (passo >= 3) {
        mostrando = false;
        passo = 0;
        delay(1000); // pausa antes de começar entrada
      }
    }
  }

  // ===== ENTRADA DO USUÁRIO =====
  else {

    bool l1 = digitalRead(bt1);
    bool l2 = digitalRead(bt2);

    // botão 1 → LED1
    if (ult1 == HIGH && l1 == LOW) {
      entrada[passo] = 1;
      passo++;
      delay(200);
    }

    // botão 2 → conta cliques
    if (ult2 == HIGH && l2 == LOW) {
      cliquesBt2++;
      ultimoClique = millis();
      delay(200);
    }

    // verifica se parou de clicar no botão 2
    if (cliquesBt2 > 0 && millis() - ultimoClique > 500) {
      if (cliquesBt2 == 1) entrada[passo] = 2;
      if (cliquesBt2 == 2) entrada[passo] = 3;

      passo++;
      cliquesBt2 = 0;
    }

    ult1 = l1;
    ult2 = l2;

    // ===== VERIFICA RESULTADO =====
    if (passo >= 3) {
      bool certo = true;

      for (int i = 0; i < 3; i++) {
        if (entrada[i] != seq[i]) {
          certo = false;
        }
      }

      // ===== FEEDBACK =====
      if (certo) {
        // pisca todos (acertou)
        for (int i = 0; i < 3; i++) {
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          delay(200);
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          delay(200);
        }
      } else {
        // pisca LED2 (erro)
        for (int i = 0; i < 3; i++) {
          digitalWrite(led2, HIGH);
          delay(200);
          digitalWrite(led2, LOW);
          delay(200);
        }
      }

      // reinicia jogo
      passo = 0;
      mostrando = true;
    }
  }
}