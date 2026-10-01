# Etapa 2

Com a arquitetura e os requisitos definidos na etapa anterior, esta etapa escolhe os componentes e detalha o projeto eletrônico. Para cada bloco foram levantadas alternativas comerciais e comparadas contra os requisitos da Etapa 1. Em seguida foram desenvolvidos os diagramas de estados do firmware e do software, os esquemáticos de comunicação e de alimentação, e o modelo 3D da estrutura de ensaio.

## Desenvolvimento

### Definição dos componentes

[...]

### Diagrama de estados do firmware e do software

O firmware atende um comando por vez a partir de OCIOSO, executa, responde ao computador e volta a esperar. Na partida ele verifica os periféricos antes de aceitar qualquer comando de ensaio.

![Diagrama de estados do firmware](assets/Imagens_e_diagrama/Diagrama_Estados-Firmware.svg)

O software conduz o ensaio: prepara, repete o ciclo de medição e encerra exportando o arquivo. Dois estados vêm da norma, o ajuste de largura e altura da bancada, e o descanso de 4 h antes de repetir o mesmo protetor em outra configuração.

![Diagrama de estados do software](assets/Imagens_e_diagrama/Diagrama_Estados-Software.svg)

**Decisão de projeto:** quem carimba o instante da liberação (t0) é a placa, com o próprio relógio, devolvendo o valor na confirmação. O computador conta os 120 s a partir desse valor, o que tira o atraso variável do USB da conta, relevante porque a janela da norma é de apenas ±5 s.

[...]

### Esquemático no KiCad

**ESP32-S3-WROOM-1 — Microcontrolador.** Lê os sensores, comanda o motor e troca dados com o computador.

![Microcontrolador](assets/Circuitos/esp32s3_microcontrolador.png)

**ADS1232IPW — ADC da célula de carga.** Amplifica e digitaliza o sinal de força.

![ADC da célula de carga](assets/Circuitos/ads1232_adc_celula_de_carga.png)

**TMC2209-LA — Driver do motor de passo.** Converte os comandos em corrente nas bobinas.

![Driver do motor](assets/Circuitos/tmc2209_driver_motor.png)

**BME280 — Sensor ambiental.** Mede a temperatura e a umidade do ensaio.

![Sensor ambiental](assets/Circuitos/bme280_sensor_ambiental.png)

**INA226 — Monitor de 5 V.** Mede tensão, corrente e potência da linha de 5 V.

![Monitor de 5 V](assets/Circuitos/ina226_monitor_5v.png)

**INA226 — Monitor de 24 V.** Mede tensão, corrente e potência da linha de 24 V.

![Monitor de 24 V](assets/Circuitos/ina226_monitor_24v.png)

**TPS7A91 — Regulador 3,3 V.** Gera a tensão da parte digital e da excitação da célula.

![Regulador 3,3 V](assets/Circuitos/tps7a91_regulador_3v3.png)

**TPS25210ARPWR — eFuse 5 V.** Protege a entrada USB contra sobretensão e sobrecorrente.

![eFuse 5 V](assets/Circuitos/tps25210_efuse_5v.png)

**TPS26630RGE — eFuse 24 V.** Protege a entrada da fonte externa.

![eFuse 24 V](assets/Circuitos/tps26630_efuse_24v.png)

**USBLC6-2SC6 — Proteção ESD.** Desvia as descargas eletrostáticas do cabo USB.

![Proteção ESD](assets/Circuitos/usblc6_protecao_esd.png)

**WS2812D — LED indicador.** Sinaliza o estado do equipamento.

![LED indicador](assets/Circuitos/ws2812d_led_indicador.png)

**Botões de ação.** Quatro entradas de comando do operador.

![Botões de ação](assets/Circuitos/botoes_de_acao.png)

**Conector do display OLED.** Saída I2C para o display externo.

![Conector do display](assets/Circuitos/conector_display_oled.png)

### Desenvolvimento 3D da estrutura de ensaio

[...]

## Referências

Norma **EN 13819-1:2020** via _BSI Standards Publication_: [EN 13819-1-2020 1.pdf](https://github.com/user-attachments/files/32043709/EN.13819-1-2020.1.pdf)