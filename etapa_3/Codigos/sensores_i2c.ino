/*
 * sensores_i2c — Leitura contínua do BME280 e dos dois INA226
 *
 * Alvo:        ESP32-S3-WROOM-1-N8
 * Pinos:       SDA = GPIO47 · SCL = GPIO48
 * Bibliotecas: Wire, WiFi (core), Adafruit_BME280, INA226 (Rob Tillaart)
 * Registro:    Testes de Hardware, seção 4.4 e 4.5
 *
 * Faixas informadas à biblioteca: 0,7 A / 110 mΩ no 5 V e 4,0 A / 20 mΩ no 24 V.
 */

#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_BME280.h>
#include <INA226.h>

#define PIN_SDA 47
#define PIN_SCL 48

Adafruit_BME280 bme;
INA226 ina5(0x45);
INA226 ina24(0x40);

bool ok_bme = false, ok_5 = false, ok_24 = false;

void setup() {
  WiFi.mode(WIFI_OFF);
  btStop();

  Serial.begin(115200);
  delay(3000);
  Wire.begin(PIN_SDA, PIN_SCL);

  ok_bme = bme.begin(0x76);
  Serial.printf("BME280 (0x76):     %s\n", ok_bme ? "OK" : "FALHOU");

  ok_5 = ina5.begin();
  if (ok_5) {
    int r = ina5.setMaxCurrentShunt(0.7, 0.11);
    if (r != 0) { Serial.printf("  calib 5V falhou (%d)\n", r); ok_5 = false; }
  }
  Serial.printf("INA226 5V (0x45):  %s\n", ok_5 ? "OK" : "FALHOU");

  ok_24 = ina24.begin();
  if (ok_24) {
    int r = ina24.setMaxCurrentShunt(4.0, 0.02);
    if (r != 0) { Serial.printf("  calib 24V falhou (%d)\n", r); ok_24 = false; }
  }
  Serial.printf("INA226 24V (0x40): %s\n\n", ok_24 ? "OK" : "FALHOU");
}

void loop() {
  if (ok_bme) {
    Serial.printf("BME280   %6.2f C   %5.1f %%RH   %6.1f hPa\n",
      bme.readTemperature(), bme.readHumidity(), bme.readPressure() / 100.0F);
  }
  if (ok_5) {
    Serial.printf("5V       %6.3f V   %6.1f mA   %7.1f mW   (shunt %6.3f mV)\n",
      ina5.getBusVoltage(), ina5.getCurrent_mA(),
      ina5.getPower_mW(), ina5.getShuntVoltage_mV());
  }
  if (ok_24) {
    Serial.printf("24V      %6.3f V   %6.1f mA   %7.1f mW   (shunt %6.3f mV)\n",
      ina24.getBusVoltage(), ina24.getCurrent_mA(),
      ina24.getPower_mW(), ina24.getShuntVoltage_mV());
  }
  Serial.println();
  delay(2000);
}
