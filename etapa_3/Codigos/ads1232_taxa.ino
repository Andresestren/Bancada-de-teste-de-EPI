/*
 * ads1232_taxa — Contagem de bordas do DRDY para validar a taxa de conversão
 *
 * Alvo:        ESP32-S3-WROOM-1-N8
 * Pinos:       DOUT/DRDY = GPIO9 · SCLK = GPIO10 · PWDN = GPIO11
 * Bibliotecas: nenhuma
 * Registro:    Testes de Hardware, seção 4.6
 *
 * Saída esperada: ~20 bordas por janela de 2 s, ou seja 10,0 SPS.
 * A primeira janela conta menos por incluir a acomodação após o reset pelo PWDN.
 * Este sketch conta bordas sem ler os dados, portanto não emite pulsos que o
 * conversor possa interpretar como instrução.
 */

#define PIN_PWDN 11
#define PIN_SCLK 10
#define PIN_DOUT  9

void setup() {
  Serial.begin(115200);
  delay(3000);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_SCLK, LOW);
  pinMode(PIN_PWDN, OUTPUT);
  digitalWrite(PIN_PWDN, LOW);   // reset
  delay(10);
  digitalWrite(PIN_PWDN, HIGH);  // acorda
  pinMode(PIN_DOUT, INPUT);
  Serial.println("Contando bordas de DRDY por 2s (esperado ~20)");
}

void loop() {
  int ant = digitalRead(PIN_DOUT);
  int n = 0;
  unsigned long t0 = millis();
  while (millis() - t0 < 2000) {
    int at = digitalRead(PIN_DOUT);
    if (at == LOW && ant == HIGH) n++;
    ant = at;
  }
  Serial.printf("bordas: %d\n", n);
  delay(500);
}
