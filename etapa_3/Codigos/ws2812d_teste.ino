/*
 * ws2812d_teste — Sequência de cores no LED indicador WS2812D
 *
 * Alvo:        ESP32-S3-WROOM-1-N8
 * Pinos:       DIN = GPIO17
 * Bibliotecas: Adafruit_NeoPixel, WiFi (core)
 * Registro:    Testes de Hardware, seção 4.2
 *
 * Saída esperada: vermelho, verde, azul, branco e apagado, 1,5 s cada.
 */

#include <Adafruit_NeoPixel.h>
#include <WiFi.h>

#define LED_PIN   17
#define LED_COUNT 1

Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  WiFi.mode(WIFI_OFF);
  btStop();
  Serial.begin(115200);
  delay(3000);
  led.begin();
  led.setBrightness(50);
  led.show();
  Serial.println("Teste WS2812D");
}

void mostra(const char *nome, uint8_t r, uint8_t g, uint8_t b) {
  Serial.println(nome);
  led.setPixelColor(0, led.Color(r, g, b));
  led.show();
  delay(1500);
}

void loop() {
  mostra("vermelho", 255, 0, 0);
  mostra("verde",    0, 255, 0);
  mostra("azul",     0, 0, 255);
  mostra("branco",   255, 255, 255);
  mostra("apagado",  0, 0, 0);
  delay(1000);
}
