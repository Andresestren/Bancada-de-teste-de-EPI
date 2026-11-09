/*
 * tmc2209_uart — Verificação da UART de fio único com o driver TMC2209
 *
 * Alvo:        ESP32-S3-WROOM-1-N8
 * Pinos:       TX = GPIO43 · RX = GPIO44 · EN = GPIO40 (ativo em nível baixo)
 * Bibliotecas: TMCStepper
 * Registro:    Testes de Hardware, seção 4.7
 *
 * Rodar com os 24 V desligados. Saída esperada: version 0x21, que confirma o
 * driver respondendo no endereço 0b00 fixado por hardware.
 */

#include <TMCStepper.h>

#define R_SENSE   0.11f
#define DRIVER_ADDR 0b00
#define PIN_EN    40

TMC2209Stepper driver(&Serial1, R_SENSE, DRIVER_ADDR);

void setup() {
  Serial.begin(115200);
  delay(3000);

  pinMode(PIN_EN, OUTPUT);
  digitalWrite(PIN_EN, HIGH);        // driver desabilitado

  Serial1.begin(115200, SERIAL_8N1, 44, 43);  // RX=RXD0, TX=TXD0
  driver.begin();
  delay(100);

  uint8_t v = driver.version();
  Serial.printf("version: 0x%02X\n", v);

  if (v == 0x21) {
    Serial.println("UART OK");
    Serial.printf("  IFCNT: %u\n", driver.IFCNT());
    Serial.printf("  DRV_STATUS: 0x%08X\n", driver.DRV_STATUS());
    Serial.printf("  ota (sobretemp): %d\n", driver.ot());
    Serial.printf("  s2ga/s2gb (curto): %d %d\n", driver.s2ga(), driver.s2gb());
  } else {
    Serial.println("sem resposta — checar UART, VCC_IO ou enderecamento");
  }
}

void loop() {}
