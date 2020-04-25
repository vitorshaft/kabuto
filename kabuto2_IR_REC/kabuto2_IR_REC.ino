/*Sketch made on 24-April-2020
 * Vitor Domingues
 * vitordomingues@ymail.com
 * https://github.com/vitorshaft/kabuto
 * This sketch was developed for Arduino robot using L29X IC as H-Bridge.
 * This sketch is for the IR version of Kabuto
 */
#include <SoftwareSerial.h>

#define buz 5
#define RX 7
#define TX 8
#define laser 13
int valor = 0;
int vidas = 3;

SoftwareSerial bluetooth = SoftwareSerial(RX,TX,false);

void contador(){
  int freq = 264;
  vidas--;
  //freq = (vidas*33)+freq;
  tone(buz,440);
  delay(1000);
  noTone(buz);
  if(vidas<=0){
    //digitalWrite(LED,HIGH);// substituir por bluetooth disconnect
    Serial.end();
  }
}

void setup() {
  pinMode(buz, OUTPUT); //define buzzer (pin D5) as output
  pinMode(RX, INPUT); //define LDR liht sensor (pin A0) as input
 
  pinMode(13,OUTPUT); //define pin 13 (laser) as output
  pinMode(9, OUTPUT); //define pin 9 (motor A) as output
  pinMode(10,OUTPUT); //define pin 10 (motor A) as output
  pinMode(11, OUTPUT); //define pin 11 (motor B) as output
  pinMode(12,OUTPUT); //define pin 12 (motor B) as output
  Serial.begin(9600);
  bluetooth.begin(9600); //Start Serial Communication (bluetooth)
  
  //Interrupt pins can be only digital pins 2 or 3
  attachInterrupt(digitalPinToInterrupt(2), contador, RISING);  //interrupt reading on digital pin 2
  digitalWrite(9,LOW);      //de-activates motor A
  digitalWrite(10,LOW);     //de-activates motor A
  digitalWrite(11,LOW);      //de-activates motor B
  digitalWrite(12,LOW);     //de-activates motor B
}

void loop() {
  digitalWrite(buz,LOW);
  
  if(bluetooth.available()){       //check if the module is receiving anything via bluetooth
    int recebe = bluetooth.read(); //"recebe" is portuguese for "receive"
    int valor = recebe-48;
    Serial.println(valor);     //show on Serial Monitor the value received via bluetooth
    if(valor==1){         //The value is added on 48 units because of the comms protocol
      digitalWrite(laser,HIGH);    //turns on the laser attached to pin 13 (change 13 to any other pin number if you want)
    }
    else if(valor==0){    //if the received value is 0...
      digitalWrite(laser,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,LOW);      //de-activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);      //de-activates motor B
      digitalWrite(12,LOW);
      
    }
    else if(valor==54){    //if the received value is 54...
      digitalWrite(laser,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,HIGH);      //activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);     //activates motor B
      digitalWrite(12,HIGH);
    }
    else if(valor==52){    //if the received value is 52...
      digitalWrite(laser,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,HIGH);      //activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);     //de-activates motor B
      digitalWrite(12,LOW);
    }
    else if(valor==53){    //if the received value is 53...
      digitalWrite(laser,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,LOW);      //de-activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);     //activates motor B
      digitalWrite(12,HIGH);
    }
    else if(valor==68){
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,LOW);      //activates motor A
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);     //activates motor B
      digitalWrite(12,LOW);
    }
    
  }
}
