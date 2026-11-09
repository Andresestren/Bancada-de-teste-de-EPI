/*
 * ads1232_leitura — Leitura da célula de carga pela interface serial do ADS1232
 *
 * Alvo:        ESP32-S3-WROOM-1-N8
 * Pinos:       DOUT/DRDY = GPIO9 · SCLK = GPIO10 · PWDN = GPIO11
 * Bibliotecas: nenhuma
 * Registro:    Testes de Hardware, seção 4.6
 *
 * Imprime a média de 10 conversões consecutivas (≈ 1 s de dados).
 * O 25º pulso de SCLK é o pulso de instrução que mantém o canal atual na
 * próxima conversão. Sem ele o conversor não libera o DRDY — ver seção 4.6.
 */

#define PIN_PWDN 11
#define PIN_SCLK 10
#define PIN_DOUT  9

long lerADS() {
  while (digitalRead(PIN_DOUT) == HIGH) { }   // espera DRDY
  long v = 0;
  for (int i = 0; i < 24; i++) {
    digitalWrite(PIN_SCLK, HIGH);
    delayMicroseconds(1);
    v = (v << 1) | digitalRead(PIN_DOUT);
    digitalWrite(PIN_SCLK, LOW);
    delayMicroseconds(1);
  }
  digitalWrite(PIN_SCLK, HIGH);               // 25o pulso
  delayMicroseconds(1);
  digitalWrite(PIN_SCLK, LOW);
  if (v & 0x800000) v |= ~0xFFFFFFL;          // extensao de sinal
  return v;
}

void setup() {
  Serial.begin(115200);
  delay(3000);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_SCLK, LOW);
  pinMode(PIN_PWDN, OUTPUT);
  digitalWrite(PIN_PWDN, LOW);
  delay(10);
  digitalWrite(PIN_PWDN, HIGH);
  pinMode(PIN_DOUT, INPUT);
  delay(500);
}

void loop() {
  long soma = 0;
  for (int i = 0; i < 10; i++) soma += lerADS();
  Serial.println(soma / 10);
}
