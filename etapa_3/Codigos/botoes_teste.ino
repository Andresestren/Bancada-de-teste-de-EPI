/*
 * botoes_teste — Leitura dos quatro botões de ação
 *
 * Alvo:        ESP32-S3-WROOM-1-N8
 * Pinos:       B1 = GPIO41 · B2 = GPIO42 · B3 = GPIO2 · B4 = GPIO1
 * Bibliotecas: WiFi (core)
 * Registro:    Testes de Hardware, seção 4.3
 *
 * Lógica ativa em nível baixo. Sem pull-up interno: o pull-up é externo.
 */

#include <WiFi.h>

const uint8_t PINOS[4] = {41, 42, 2, 1};  // B1, B2, B3, B4

void setup() {
  WiFi.mode(WIFI_OFF);
  btStop();
  Serial.begin(115200);
  delay(3000);
  for (int i = 0; i < 4; i++) pinMode(PINOS[i], INPUT);
  Serial.println("Teste botoes (pressionado = 0)");
}

void loop() {
  Serial.print("B1:"); Serial.print(digitalRead(41));
  Serial.print("  B2:"); Serial.print(digitalRead(42));
  Serial.print("  B3:"); Serial.print(digitalRead(2));
  Serial.print("  B4:"); Serial.println(digitalRead(1));
  delay(300);
}
