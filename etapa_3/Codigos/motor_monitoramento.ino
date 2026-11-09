/*
 * motor_monitoramento — Acionamento do motor de passo com monitoramento integrado
 *
 * Alvo:        ESP32-S3-WROOM-1-N8
 * Pinos:       STEP = GPIO38 · DIR = GPIO37 · EN = GPIO40 · DIAG = GPIO39 · UART 43/44 · I2C 47/48
 * Bibliotecas: TMCStepper, AccelStepper, INA226 (Rob Tillaart), Adafruit_BME280
 * Registro:    Testes de Hardware, seção 4.7
 *
 * Mede consumo em quatro condições: driver off, eixo travado, girando e parado
 * com corrente de hold. Requer os 24 V ligados.
 */

/*
 * Motor de passo + monitoramento completo
 * TMC2209-LA + INA226 (5V e 24V) + BME280 — ESP32-S3-WROOM-1-N8
 *
 * Bibliotecas: TMCStepper, AccelStepper, INA226 (Rob Tillaart), Adafruit BME280
 */

#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_BME280.h>
#include <INA226.h>
#include <TMCStepper.h>
#include <AccelStepper.h>

// ---------- Pinos ----------
#define PIN_SDA      47
#define PIN_SCL      48
#define PIN_STEP     38
#define PIN_DIR      37
#define PIN_EN       40   // ativo em nivel BAIXO
#define PIN_DIAG     39
#define PIN_UART_TX  43
#define PIN_UART_RX  44

// ---------- Driver ----------
#define R_SENSE       0.11f
#define DRIVER_ADDR   0b00
#define MICROSTEPS    16

// =============== CONFIGURACAO ===============
#define CORRENTE_RMS    900    // mA RMS (teto do hardware: 1170)
#define CORRENTE_PARADO 50     // % da corrente com o eixo parado
#define PASSOS_VOLTA    200
#define VELOCIDADE      3000   // micropassos por segundo
#define ACELERACAO      6000   // micropassos por segundo^2
#define VOLTAS          2
#define PAUSA_MS        2000   // pausa entre movimentos
// ============================================

Adafruit_BME280 bme;
INA226 ina5(0x45);
INA226 ina24(0x40);
bool ok_bme = false, ok_5 = false, ok_24 = false;

HardwareSerial SerialTMC(1);
TMC2209Stepper driver(&SerialTMC, R_SENSE, DRIVER_ADDR);
AccelStepper motor(AccelStepper::DRIVER, PIN_STEP, PIN_DIR);
bool ok_drv = false;

const long PASSOS_MOV = (long)PASSOS_VOLTA * MICROSTEPS * VOLTAS;

bool indo = true;
bool pausado = false;
bool mediuEmMovimento = false;
unsigned long inicioPausa = 0;
unsigned long inicioMov = 0;

void setup() {
  WiFi.mode(WIFI_OFF);
  btStop();
  Serial.begin(115200);
  delay(3000);

  pinMode(PIN_EN, OUTPUT);
  digitalWrite(PIN_EN, HIGH);        // driver desabilitado
  pinMode(PIN_DIAG, INPUT);

  // ---------- I2C ----------
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
  Serial.printf("INA226 24V (0x40): %s\n", ok_24 ? "OK" : "FALHOU");

  // ---------- Driver do motor ----------
  SerialTMC.begin(115200, SERIAL_8N1, PIN_UART_RX, PIN_UART_TX);
  delay(100);

  driver.begin();
  driver.I_scale_analog(false);      // ignora VREF, usa registradores
  driver.toff(5);
  driver.rms_current(CORRENTE_RMS, CORRENTE_PARADO / 100.0f);
  driver.microsteps(MICROSTEPS);
  driver.pwm_autoscale(true);
  driver.en_spreadCycle(false);      // StealthChop2
  driver.iholddelay(8);
  driver.TPOWERDOWN(20);

  uint8_t v = driver.version();
  ok_drv = (v != 0 && v != 0xFF);
  Serial.printf("TMC2209 (UART):    %s\n\n", ok_drv ? "OK" : "FALHOU (24V ligados?)");

  motor.setMaxSpeed(VELOCIDADE);
  motor.setAcceleration(ACELERACAO);
  motor.setCurrentPosition(0);

  medir("driver off");

  digitalWrite(PIN_EN, LOW);         // habilita
  delay(300);
  medir("eixo travado");
  Serial.println();

  motor.moveTo(PASSOS_MOV);
  inicioMov = millis();
}

void loop() {
  if (!pausado) {
    motor.run();                     // nao pode ser bloqueado

    if (!mediuEmMovimento && millis() - inicioMov > 700) {
      mediuEmMovimento = true;
      medir("girando");
    }

    if (motor.distanceToGo() == 0) {
      pausado = true;
      inicioPausa = millis();
      verificarFalhas();
    }
  } else {
    if (millis() - inicioPausa >= PAUSA_MS) {
      medir("parado");
      Serial.println();
      pausado = false;
      mediuEmMovimento = false;
      indo = !indo;
      motor.moveTo(indo ? PASSOS_MOV : 0);
      inicioMov = millis();
    }
  }
}

void medir(const char *rotulo) {
  Serial.printf("=== %s ===\n", rotulo);

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
}

void verificarFalhas() {
  if (driver.otpw()) Serial.println("!! Pre-aviso termico do driver");
  if (driver.ot())   Serial.println("!! DESARME TERMICO do driver");
  if (driver.s2ga() || driver.s2gb()) Serial.println("!! Curto em bobina");
}
