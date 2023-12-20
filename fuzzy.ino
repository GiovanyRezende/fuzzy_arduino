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
const int led_test = 4;

void setup() {
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  
  pinMode(led_test,OUTPUT);
  pinMode(Button,INPUT);
}

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
  
  if (T <= 18){
    y = 0;
  }
  else if (T>18 && T<21){
    y = ((T-18)/(21-18)) * 255; //map(T, 18, 21, 0, 255);
  }
  else if (T >= 21 && T <= 24){
    y = 255;
  }
  else if (T > 24 && T < 27){
    y = ((24-T)/(27-24)) * 255; //map(T, 24, 27, 255, 0);
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

void loop() {
  DHT.read11(temp);
  
  int  r = hot(DHT.temperature);
  int  g = comf(DHT.temperature);
  int  b = cold(DHT.temperature);
  
  currentButton = debounce(lastButton);
  
  if (lastButton == LOW && currentButton == HIGH)
  {
    something = !something;
  }
  lastButton = currentButton;
  
  if (something == false){
    digitalWrite(led_test,LOW);
    
    if (DHT.temperature <= 21){
      digitalWrite(blue,HIGH);
    }
    else{
      digitalWrite(blue,LOW);
    }

    if (DHT.temperature >= 18 && temp <= 27){
      digitalWrite(green,HIGH);
    }
    else{
      digitalWrite(green,LOW);
    }

    if (DHT.temperature  >= 24){
      digitalWrite(red,HIGH);
    }
    else{
      digitalWrite(red,LOW);
    }
  }
  
  else if (something == true){
    digitalWrite(led_test,HIGH);
    
    analogWrite(red,r);
    analogWrite(green,g);
    analogWrite(blue,b); 
  }  
  
}