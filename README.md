# Projeto Lógica Fuzzy

*Este projeto tem o objetivo de aplicar a Lógica Fuzzy em um circuito de Arduino, servindo como demonstração de como ela é importante para uma Inteligência Artificial.* Na Matemática, a Lógica Fuzzy (ou Lógica Nebulosa) é diferente da comum Lógica Proposicional. Enquanto a segunda diz se proposições são verdadeiras ou falsas, a primeira diz o quão uma proposição é verdadeira (ou falsa). Uma propriedade desse ramo matemático é poder expressar em valores numéricos a linguagem natural (LN). As seguintes definições exemplificam essa afirmação:
- Quente ou frio;
- Perto ou longe;
- Alto ou baixo;
- Desempenho bom ou desempenho ruim;
- Grande ou pequeno.

Não dá para extrair um valor lógico de "A temperatura XºC é quente" em verdadeiro ou falso em todos os casos, mas sim a porcentagem da veracidade ("O quão quente é XºC"). A temperatura é o exemplo que será abordado no circuito.

# O funcionamento do circuito
O circuito acende as cores de um LED RGB de acordo com a temperatura ambiente. Ainda, há dois modos: *o modo de Lógica Proposicional e o modo de Lógica Fuzzy*. Com essas duas configurações, é possível comparar os funcionamentos das duas lógicas em um agente.

# Os materiais

|Item|Quantidade|
| - | - |
|Arduino Uno|1|
|LED RGB|1|
|Botão|1|
|Resistor 220 Ω|3 ou 4|
|Sensor de temperatura DHT11|1|
|LED vermelho (opcional)|1|
|Jumpers ou conexões|±11|

# O circuito e suas conexões
![logica_fuzzy](https://github.com/GiovanyRezende/fuzzy_arduino/assets/111097597/e0cc3f4e-4de6-42e3-9db3-d7acf32736d4)
**Nota: o sensor DHT11 está sendo representado por um sensor de temperatura LM35. Considere o pino OUT do LM35 como o pino DATA do DHT11 desse projeto.**

# O gráfico dos conjuntos nebulosos
![WhatsApp Image 2023-12-20 at 20 46 57](https://github.com/GiovanyRezende/fuzzy_arduino/assets/111097597/dca6d456-1185-4b35-a292-1ac3b5735538)

