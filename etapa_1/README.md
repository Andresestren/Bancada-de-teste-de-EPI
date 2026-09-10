# Etapa 1

A etapa 1 define a arquitetura do equipamento antes da escolha dos componentes. Foram produzidos o diagrama de blocos de hardware e comunicação, a especificação funcional de cada bloco, o esboço da estrutura 3D e o levantamento da norma aplicável. Com a arquitetura fechada e os requisitos definidos, a seleção dos componentes na etapa seguinte passa a ser feita por critério técnico. **[Ajustar: acrescentar uma frase dizendo o que o equipamento faz.]**

## Desenvolvimento

### Diagrama de blocos de hardware e comunicação

![Diagrama de blocos](assets/Imagens_e_diagrama/Diagrama_DEFA.svg)

**Alimentação**

| Bloco | Função |
| :--- | :--- |
| **Entrada de 24 V** | Fonte externa que alimenta a parte de potência do motor. |
| **Proteção da entrada de 24 V** | Só alimenta o circuito em condição segura, cortando a energia em caso de falha. |
| **Monitor de energia (24 V)** | Mede tensão, corrente e potência dessa linha. |
| **Entrada USB (5 V)** | Alimenta a eletrônica de sinal e conecta o equipamento ao computador. |
| **Proteção da entrada de 5 V** | Mesma função, aplicada à linha de 5 V. |
| **Monitor de energia (5 V)** | Mede o consumo da linha de 5 V. |
| **Regulador de tensão** | Reduz os 5 V para os 3,3 V usados pela parte digital. |

**Controle e medição**

| Bloco | Função |
| :--- | :--- |
| **Microcontrolador** | Centro do sistema: lê os sensores, comanda o motor, atualiza o display e troca dados com o computador. |
| **Proteção ESD da USB** | Desvia as descargas eletrostáticas do cabo antes que alcancem o microcontrolador. |
| **Entrada da célula de carga** | Recebe o sinal de peso do sensor externo. |
| **Conversor A/D** | Amplifica e digitaliza o sinal da célula de carga. |
| **Sensor de temperatura e umidade** | Mede as condições do ambiente de operação. |

**Acionamento e interface**

| Bloco | Função |
| :--- | :--- |
| **Driver do motor de passo** | Converte os comandos do microcontrolador em corrente nas bobinas do motor. |
| **Saída para o motor** | Conexão do motor de passo ao equipamento. |
| **Botões de ação (4)** | Entrada dos comandos do operador. |
| **LED indicador** | Sinaliza o estado de funcionamento. |
| **Saída para o display** | Apresenta as informações ao operador. |

### Especificação dos componentes de hardware

Os componentes ainda não foram definidos; esta seção estabelece o que cada bloco precisa atender. O sistema é alimentado por 24 V (potência do motor) e por 5 V da porta USB, que é também o canal de comunicação com o software de PC que opera o equipamento. Toda a parte digital opera em 3,3 V.

| Bloco | O que precisa atender |
| :--- | :--- |
| **Proteção das entradas (2)** | Desligar por subtensão ou sobretensão, limitar a corrente, partida suave e sinalizar falha. A de 24 V suporta corrente maior; a de 5 V respeita o limite de uma porta USB. |
| **Regulador 5 V → 3,3 V** | Corrente para toda a parte digital e baixo ruído, pois a mesma tensão alimenta o circuito de pesagem. |
| **Monitores de energia (2)** | Medir tensão, corrente e potência das linhas de 5 V e 24 V. |
| **Microcontrolador** | Pinos para todos os blocos; sinais em 3,3 V; comunicação USB para gravação e para o software do computador; pulsos com temporização precisa. |
| **Conversor A/D** | Sinal diferencial de poucos milivolts: amplificar, converter com alta resolução, filtrar a interferência da rede e manter a leitura estável. |
| **Sensor de temperatura e umidade** | Saída digital já calibrada, ±1 °C e ±3 % de umidade, alimentação em 3,3 V. |
| **Driver do motor de passo** | Motor bipolar NEMA 17 em 24 V; passo, direção e habilitação; micropassos; desligado por padrão ao energizar; proteção térmica e de sobrecorrente. |
| **Botões (4)** | Comandos do operador e durabilidade para uso frequente. |
| **LED indicador** | Estado do equipamento em mais de uma cor, com o mínimo de pinos. |
| **Conector do display** | Display externo, ligado por cabo; conector polarizado e com travamento. |
| **Proteção da porta USB** | Desviar as descargas eletrostáticas sem degradar o sinal. |
| **Conectores externos** | Folga de corrente no 24 V e no motor; boa fixação do USB; conectores distintos entre si. |

A comunicação entre os blocos será digital, em 3,3 V, com preferência por periféricos que compartilhem o mesmo barramento para economizar pinos. As interfaces serão definidas junto com a escolha dos componentes.

### Esboço da estrutura 3D

**[ imagens do esboço.]**
Descrever: dimensões aproximadas, o motor, a célula de carga.

### Norma aplicável

**[A ESCREVER ]**



## Referências (links/datasheets/livros)

**[A COMPLETAR — incluir a norma citada e as fontes consultadas. Toda referência precisa estar citada no texto.]**