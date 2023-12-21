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

**Nota: o sensor DHT11 está sendo representado por um sensor de temperatura LM35. Considere o pino OUT do LM35 como o pino DATA do DHT11 desse projeto. Além disso, considere as conexões dos pinos do RGB condizentes com as cores do seu LED, assim como o pino usado para o LED vermelho opcional que pode variar com o circuito.**

# O gráfico dos conjuntos nebulosos
Os conjuntos nebulosos são três: ```Frio```, ```Confortável``` e ```Quente```. A classificação das temperaturas foi baseada na seguinte tabela ([mais detalhes são encontrados nesse blog, porém, o projeto não abordou mais do que a tabela indica](https://irrigacao.blogspot.com/2012/09/conforto-termico.html)):

![](https://3.bp.blogspot.com/-d7dGcxdnV8w/UFd7bLdylDI/AAAAAAAAAD0/WnAbp3Ngun4/s320/Imagem1.png)

Esses conjuntos são descritos por funções trapezoidais baseadas na tabela. Entretanto, se seguida sem ajustes, considerando por exemplo que a amplitude de ```Confortável``` é de 18ºC à 27ºC, o gráfico fica assim:
![conjuntos_nebulosos_arduino](https://github.com/GiovanyRezende/fuzzy_arduino/assets/111097597/5806b0ba-3977-4fb6-8330-5450a4b975d3)

É possível notar por meio das intersecções que esse gráfico viola a Teoria dos Conjuntos. Como é possível uma temperatura ser 25% fria, 25% confortável e 50% nenhuma classificação? Para ficar matematicamente correto, o gráfico final é o mostrado à seguir:
![conjuntos_nebulosos_arduino](https://github.com/GiovanyRezende/fuzzy_arduino/assets/111097597/e80ecb22-439a-4822-844a-61a4d2f97158)

É perceptível que, na Lógica Fuzzy, 0 e 1 (falso e verdadeiro da Lógica Proposicional) existem, mas é possível um valor como 0.5 (50% verdadeiro ou 50% falso), desde que seja entre os dois valores booleanos ditos. No gráfico final, 32ºC é cerca de 88,89% verdadeiro em ```Quente``` e 11,11% verdadeiro em ```Confortável```, por exemplo.

# O código

# Conclusão

