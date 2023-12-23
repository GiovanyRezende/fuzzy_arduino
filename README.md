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

## Bibliotecas e declaração de constantes e variáveis
```
#include <math.h>
#include "dht.h"

const int red = 9;
const int green = 10;
const int blue = 11;

const int temp = A2;
dht DHT;

const int Button = 2;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean something = false;
const int led_test = 4; //na figura, está sendo representado pelo pino 3
```

## Setup
```
void setup() {
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  
  pinMode(led_test,OUTPUT);
  pinMode(Button,INPUT);
}
```
## Funções trapezoidais
```
int cold(float T){
  int x;
  
  if (T <= 12){
    x = 255;
  }
  else if (T > 12 && T < 21){
    x = ((21-T)/(21-12)) * 255; //map(T, 12, 21, 255, 0);
  }
  else if (T >= 21){
    x = 0;
  }
  return round(x);
}

int comf(float T){
  int y;
  
  if (T <= 12){
    y = 0;
  }
  else if (T>12 && T<21){
    y = ((T-12)/(21-12)) * 255; //map(T, 18, 21, 0, 255);
  }
  else if (T >= 21 && T <= 24){
    y = 255;
  }
  else if (T > 24 && T < 33){
    y = ((33-T)/(33-24)) * 255; //map(T, 24, 27, 255, 0);
  }
  else {
    y = 0;
  }
  return round(y);
}

int hot(float T){
  int z;
  
  if (T <= 24){
    z = 0;
  }
  else if (T > 24 && T < 33){
    z = ((T-24)/(33-24)) * 255; //map(T, 24, 33, 0, 255);
  }
  else if (T >= 33){
    z = 255;
  }
  return round(z);
}
```

## Função que muda a Lógica operante no circuito
```
boolean debounce(boolean last)
{
  boolean current = digitalRead(Button);
  if (last != current)
  {
    delay(5);
    current = digitalRead(Button);
  }
  return current;
}
```

## Loop
```DHT.read11(temp)``` é o comando que extrai os dados de temperatura/umidade do DHT11 e ```DHT.temperature``` é o valor da temperatura medida pelo sensor. Quando ```something``` é falso, o LED opcional fica apagado e o loop executa:
```
digitalWrite(led_test,LOW);
    
    if (DHT.temperature < 21){
      digitalWrite(blue,HIGH);
    }
    else{
      digitalWrite(blue,LOW);
    }

    if (DHT.temperature > 12 && temp < 33){
      digitalWrite(green,HIGH);
    }
    else{
      digitalWrite(green,LOW);
    }

    if (DHT.temperature  > 24){
      digitalWrite(red,HIGH);
    }
    else{
      digitalWrite(red,LOW);
    }
  }
```
Resumindo, nesse modo, é a Lógica Proposicional que está operando.

Quando ```something``` é verdadeiro, o LED vermelho acende, mostrando que o modo operante é o da Lógica Fuzzy, e o loop executa:
```
digitalWrite(led_test,HIGH);
    
    analogWrite(red,r);
    analogWrite(green,g);
    analogWrite(blue,b); 
```
sendo que ```r```, ```g``` e ```b``` são previamente computados como:
```
  int  r = hot(DHT.temperature);
  int  g = comf(DHT.temperature);
  int  b = cold(DHT.temperature);
```

## Análise do funcionamento
Analisando as cores do RGB no funcionamento da Lógica Proposicional, elas seguem o seguinte diagrama, uma vez que não há intersecções das três cores e de vermelho com azul:

![](https://s4.static.brasilescola.uol.com.br/img/2019/04/sintese-aditiva(1).jpg)

Com a Lógica Proposicional, o circuito aplicará 5V tanto no pino vermelho como no verde quando a temperatura que o sensor medir for 32ºC, pois essa temperatura está amplitude do ```Confortável``` e do ```Quente```.
Já com a Lógica Nebulosa, o circuito aplicará uma porcentagem dos 5V, que vai de 0% à 100%. Em 32ºC, será aplicada uma tensão de 88,89% de 5V no pino vermelho e 11,11% de 5V no pino verde.

# Conclusão
Observando a diferença de comportamento do circuito entre as duas lógicas na mesma temperatura, é possível concluir que nem sempre a Lógica Proposicional é o suficiente para um projeto de Inteligência Artificial. No próprio exemplo da temperatura em 32ºC, a Lógica Proposicional diria que está entre o ```Confortável``` e o ```Quente```, mas não seria possível saber o quão intensas seriam essas classificações, o que se distancia da Linguagem Natural. Agora, com a Lógica Fuzzy, o agente consegue expressar que 32ºC é muito mais ```Quente``` do que ```Confortável```, aproximando a classificação de dados da LN.

<div align= center>

# Redes sociais e formas de contato



[![logo](https://cdn-icons-png.flaticon.com/256/174/174857.png)](https://br.linkedin.com/in/giovanyrezende)
[![logo](https://images.crunchbase.com/image/upload/c_lpad,f_auto,q_auto:eco,dpr_1/v1426048404/y4lxnqcngh5dvoaz06as.png)](https://github.com/GiovanyRezende)[
![logo](https://logospng.org/download/gmail/logo-gmail-256.png)](mailto:giovanyrmedeiros@gmail.com)

</div>

