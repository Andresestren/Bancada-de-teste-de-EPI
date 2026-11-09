# Códigos de teste

Sketches usados na validação da placa, um por periférico. Todos foram compilados e
gravados pela Arduino IDE, alvo **ESP32-S3-WROOM-1-N8**. Os resultados de cada um estão
registrados em [`../Testes_de_Hardware.md`](../Testes_de_Hardware.md).

| Sketch | O que testa | Seção |
| :--- | :--- | :--- |
| [`i2c_scan.ino`](i2c_scan.ino) | Varredura de endereços no barramento I2C | 4.1 |
| [`ws2812d_teste.ino`](ws2812d_teste.ino) | Sequência de cores no LED indicador | 4.2 |
| [`botoes_teste.ino`](botoes_teste.ino) | Leitura dos quatro botões de ação | 4.3 |
| [`sensores_i2c.ino`](sensores_i2c.ino) | BME280 e os dois INA226 | 4.4 e 4.5 |
| [`ads1232_taxa.ino`](ads1232_taxa.ino) | Taxa de conversão do ADS1232 | 4.6 |
| [`ads1232_leitura.ino`](ads1232_leitura.ino) | Leitura da célula de carga | 4.6 |
| [`tmc2209_uart.ino`](tmc2209_uart.ino) | UART de fio único com o driver | 4.7 |
| [`motor_monitoramento.ino`](motor_monitoramento.ino) | Motor em operação com medição de consumo | 4.7 |

## Bibliotecas

Além do core do ESP32, são necessárias:

| Biblioteca | Usada por |
| :--- | :--- |
| Adafruit NeoPixel | `ws2812d_teste` |
| Adafruit BME280 | `sensores_i2c`, `motor_monitoramento` |
| INA226 (Rob Tillaart) | `sensores_i2c`, `motor_monitoramento` |
| TMCStepper | `tmc2209_uart`, `motor_monitoramento` |
| AccelStepper | `motor_monitoramento` |

Os dois sketches do ADS1232 não usam biblioteca: a interface serial do conversor é
implementada no próprio sketch.

## Para abrir na Arduino IDE

A IDE exige que cada sketch esteja numa pasta com o mesmo nome do arquivo. Para abrir
`i2c_scan.ino`, crie a pasta `i2c_scan/` e mova o arquivo para dentro dela. Aqui os
arquivos estão soltos de propósito, para que os links do documento de testes apontem
direto para o código.

## Ordem de execução

Os sketches que acionam o motor exigem os 24 V ligados; os demais funcionam só com o
USB-C. A ordem usada na validação foi a das seções: I2C, LED, botões, sensores, ADS1232,
UART do driver e, por último, o motor em operação.

> `tmc2209_uart.ino` deve ser rodado com os **24 V desligados**: ele verifica apenas a
> comunicação, e o driver responde pela UART alimentado só pelo VCC_IO de 3,3 V.
