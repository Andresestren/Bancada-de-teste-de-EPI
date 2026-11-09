/*
 * i2c_scan — Varredura de endereços no barramento I2C
 *
 * Alvo:        ESP32-S3-WROOM-1-N8
 * Pinos:       SDA = GPIO47 · SCL = GPIO48
 * Bibliotecas: Wire, WiFi (ambas do core)
 * Registro:    Testes de Hardware, seção 4.1
 *
 * Saída esperada: 0x40 (INA226 de 24 V), 0x45 (INA226 de 5 V) e 0x76 (BME280).
 */

#include <Wire.h>
#include <WiFi.h>

void setup() {
  WiFi.mode(WIFI_OFF);
  btStop();
  Serial.begin(115200);
  delay(3000);
  Wire.begin(47, 48);
  Serial.println("Scan I2C:");
}

void loop() {
  int n = 0;
  for (uint8_t a = 1; a < 127; a++) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0) {
      Serial.printf("  encontrado: 0x%02X\n", a);
      n++;
    }
  }
  Serial.printf("total: %d\n\n", n);
  delay(3000);
}
