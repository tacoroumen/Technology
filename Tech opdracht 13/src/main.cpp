#include <Arduino.h>
#include "Display.h"

const int led_red = 4;
const int led_green = 5;
const int led_blue = 6;
const int led_yellow = 7;
const int button1 = 8;
const int button2 = 9;
const int buzzer = 3;
const int ir_reciever =2;
const int LDR = A2;
const int NTC = A1;
const int potmeter = A0;
const int DHT11 = 12;
const int seg7clock = 10;
const int seg7data = 11;
const int EEpromSCL = 19;
const int EEpromSFA = 18;
//const int NC = 13; 
const int Led_internal = 13;
const int TX = 1;
const int RX = 0;
int count = 9995;
const int max_allowed_people = 9999;
const int debounce = 200;
unsigned int lastcount = 0;
unsigned long delayledoff = 0;
unsigned long lastdebouncebutton1 = 0;
unsigned long lastdebouncebutton2 = 0;
int lightcount = 0;
const int arraysize = 10;
int sumint[arraysize];
int i = 0;
int pot;

void setup() {
  // put your setup code here, to run once:
   pinMode (led_red,OUTPUT);
   pinMode (led_green,OUTPUT);
   pinMode (led_blue,OUTPUT);
   pinMode (led_yellow,OUTPUT);
   pinMode (button1,INPUT_PULLUP);
   pinMode (button2,INPUT_PULLUP);
   pinMode (buzzer,OUTPUT);
   pinMode (ir_reciever,INPUT);
   pinMode (LDR,INPUT);
   pinMode (Led_internal,OUTPUT);
   //pinMode (NTC,INPUT);
   pinMode (potmeter,INPUT);
   pinMode (TX,OUTPUT);
   pinMode (RX,INPUT);
   Serial.begin(9600);
   Display.clear();

}
void led_blink1(int count) {
  for(int i = 0; i<count; i++){
      digitalWrite(led_yellow, HIGH);
      delay(200);
      digitalWrite(led_yellow, LOW);
      delay(200);
    }
}

void led_blink2(int count) {
  for(int i = 0; i<count; i++){
      digitalWrite(led_blue, HIGH);
      delay(200);
      digitalWrite(led_blue, LOW);
      delay(200);
    }
}

void loop() {
  // put your main code here, to run repeatedly
  pot = analogRead(potmeter);
  pot = map(pot, 0, 1023, 0, 255);
  analogWrite(led_yellow, pot);
  Serial.println(pot);
}
