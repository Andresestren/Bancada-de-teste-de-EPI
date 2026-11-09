# Etapa 3

Esta etapa passa do projeto para o hardware. O roteamento da PCI foi concluído e a placa fabricada e recebida, a estrutura foi montada e validada, e os ensaios de bancada confirmaram o funcionamento da placa, do motor e da cadeia de medição. O case da PCI teve a primeira versão reprovada na fabricação, e a segunda, redesenhada para o processo, está em produção.

## Desenvolvimento

### Diagramas de blocos completos

Os diagramas de comunicação e de alimentação foram consolidados na Etapa 2 e permanecem válidos. São reproduzidos aqui para referência.

#### Diagrama de comunicação
![Diagrama de comunicação](assets/Imagens_e_diagrama/esquematico_comunicacao.svg)

#### Diagrama de alimentação
![Diagrama de alimentação](assets/Imagens_e_diagrama/esquematico_alimentacao.svg)

### Finalização do projeto da PCI e envio para fabricação

A etapa anterior terminou no esquemático. Nesta etapa o roteamento foi concluído e a placa enviada para fabricação.

| Característica | Valor |
| :--- | :--- |
| Camadas | 2 |
| Dimensões | 100 × 70 mm |
| Espessura | 1,6 mm |
| Fabricante | JLCPCB |

Todo o circuito foi roteado com trilhas de 0,2 mm, com exceção do barramento de 24 V, em 1 mm, e das trilhas que levam às bobinas do motor, em 0,5 mm. Larguras dimensionadas para a corrente de operação. As duas camadas têm malha GND.

O sensor de temperatura e umidade ficou no canto oposto ao driver do motor, isolado por dois rasgos na placa e sem malha de cobre ligando-o ao restante: assim ele mede o ambiente do ensaio e não o aquecimento da própria placa, que é a condição exigida pela norma. A antena do módulo ESP32 ficou projetada para fora da borda da placa, como recomenda o datasheet da Espressif, e o conector da célula de carga foi posicionado junto ao conversor A/D, encurtando o trajeto do sinal diferencial.

Antes da geração dos arquivos de fabricação foram executadas as verificações de regras elétricas (ERC) e de regras de projeto (DRC).

#### Layout da PCI
![Layout da PCI](assets/Imagens_e_diagrama/pci_layout.png)

#### Vista 3D do KiCad
![Vista 3D do KiCad](assets/Imagens_e_diagrama/pci_3d.png)

#### Placa confeccionada
![Placa recebida](assets/Imagens_e_diagrama/pci_fabricada.jpg)

### Desenvolvimento 3D do case da PCI

O case foi modelado no SolidWorks. A primeira versão era dividida em duas peças, tampa e base, em alumínio de 2 mm. Na fabricação, o processo de dobra e corte não atendeu às dimensões projetadas, e a peça foi reprovada.

A segunda versão foi redesenhada em função do processo: a espessura do alumínio passou de 2 mm para 1 mm e os raios de dobra foram padronizados para chapa dessa espessura. O case também foi dividido em três peças, o que facilita tanto a produção quanto a montagem. O projeto está finalizado e a peça em produção.

#### Case versão 1
![Case versão 1](assets/Imagens_e_diagrama/case_v1.jpg)

#### Case versão 2
![Case versão 2](assets/Imagens_e_diagrama/case_v2.png)

### Montagem e ajuste da estrutura

As peças da estrutura foram desenhadas na Etapa 2 e enviadas para a Metal Porto, em Palhoça, empresa de corte e dobra de chapas de alumínio. Nesta etapa elas foram recebidas e validadas pela montagem: verificou-se o encaixe entre as peças, a rigidez do conjunto e o atendimento aos requisitos.

A estrutura foi validada quase por completo. A exceção é o suporte do pino de apoio para protetores acoplados a capacete. A peça é fixada ao suporte L deslizante e sustenta um pino centralizado na estrutura, sobre o qual o capacete se apoia, com ajuste de altura. Por ser uma chapa de 2 mm dobrada em L, ficou flexível demais e não mantém o capacete imóvel durante o ensaio. A peça será refeita com chapa mais espessa.

#### Estrutura montada
![Estrutura montada](assets/Imagens_e_diagrama/estrutura_montada.jpg)

#### Estrutura com o protetor posicionado
![Protetor auricular tipo concha montado na estrutura](assets/Imagens_e_diagrama/estrutura_protetor_frente.jpg)

#### Suporte de pino reprovado
![Suporte de pino reprovado](assets/Imagens_e_diagrama/suporte_pino_v1.jpeg)

## Testes

O registro completo da validação está em [Testes de Hardware](Testes_de_Hardware.md), com os códigos em [`Codigos/`](Codigos/). Instrumentos: multímetro Fluke 289 e osciloscópio Rigol DS4034.

### Teste do motor

Com 900 mA RMS, 16 micropassos e StealthChop2, o motor girou nos dois sentidos conforme programado. O consumo em 24 V foi de 165,2 mA girando (4,03 W) e 81,0 mA com corrente de hold, contra 10,5 mA com o driver desabilitado — 6,6 % do limite de 2,5 A do eFuse.

Esse ensaio também validou o shunt de 20 mΩ do INA226 de 24 V, que na seção de alimentação não pôde ser conferido por falta de corrente: a queda de 3,290 mV corresponde a 164,5 mA contra 165,2 mA reportados, diferença de 0,4 %.

### Teste da célula de carga

A leitura inicial do ADS1232 oscilava de forma incompatível com a célula em repouso, com
saltos periódicos para valores muito acima da faixa. A medição dos intervalos entre
conversões localizou a causa no firmware, e não no circuito: sem o pulso de instrução
após os 24 bits de dados, a leitura seguinte era interpretada pelo conversor como pedido
de calibração de offset, que o inibe por oito ciclos. A assinatura era inequívoca, 32 %
dos intervalos em 0,22 ms seguidos de 31 % em 801,5 ms, exatamente oito períodos
nominais, com taxa efetiva de 3,48 SPS contra os 10,0 de projeto.

Corrigido o pulso, 247 conversões consecutivas em 100,066 ms ± 0,05 ms, sem anomalia. A
calibração com massa padrão de 500 g resultou em 455,0 contagens/g (46.393 contagens/N),
confirmada em 453,78 contagens/g por medição independente, 0,26 % de diferença. O ruído
ficou em 0,09 g e o fundo de escala de 40 N ocupa 23 % da faixa de 24 bits. Bloco aprovado.



## Referências

Norma **EN 13819-1:2020** via _BSI Standards Publication_: [EN 13819-1-2020 1.pdf](https://github.com/user-attachments/files/32043709/EN.13819-1-2020.1.pdf)
