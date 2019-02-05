/*Sketch made on 16-December-2017
 * Vitor Domingues
 * vitordomingues@ymail.com
 * https://sites.google.com/view/vitordomingues
 * This sketch was developed for Arduino robot using ULN2003 IC as H-Bridge.
 * If your Robot uses L293 or L298 H-Bridge please refer to *_laser_robot_L29X.ino file
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6,8); // RX, TX
int LDR = A0;
int buz = 5;
int luz = 0;
int vidas = 3;
int saude = 7;

void contador(){
  vidas--;
  delay(1000);
  if(vidas<=0){
    digitalWrite(saude,HIGH);
    Serial.end();
  }
}

void setup() {
  pinMode(LDR,INPUT);
  pinMode(buz,OUTPUT);
  pinMode(saude,OUTPUT);
  pinMode(13,OUTPUT); //define pin 13 (laser) as output
  pinMode(9, OUTPUT); //define pin 9 (motor A) as output
  pinMode(10,OUTPUT); //define pin 10 (motor B) as output
  Serial.begin(9600); //Start Serial Communication (bluetooth)
  mySerial.begin(9600);
  //Serial.println("OK");
  digitalWrite(9,HIGH);      //de-activates motor A
  digitalWrite(10,HIGH);     //de-activates motor B
}

void loop() {
  if(mySerial.available()){       //check if the module is receiving anything via bluetooth
    //Serial.println("OK");
    int recebe = mySerial.read(); //"recebe" is portuguese for "receive"
    int valor = recebe;
    Serial.println(valor);//show on Serial Monitor the value received via bluetooth
    valor = recebe-48;
    if(valor==1){         //The value is added on 48 units because of the comms protocol
      digitalWrite(13,HIGH);    //turns on the laser attached to pin 13 (change 13 to any other pin number if you want)
    }
    else if(valor==0){    //if the received value is 0...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,LOW);      //de-activates motor
      digitalWrite(10,LOW);
    }
    else if(valor==54){    //if the received value is 54...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,HIGH);      //activates motor A
      digitalWrite(10,HIGH);     //activates motor B
    }
    else if(valor==52){    //if the received value is 52...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,HIGH);      //activates motor A
      digitalWrite(10,LOW);     //de-activates motor B
    }
    else if(valor==53){    //if the received value is 53...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,LOW);      //de-activates motor A
      digitalWrite(10,HIGH);     //activates motor B
    }
  }
  luz = analogRead(LDR);
  //Serial.println(luz);
  //Serial.print("vidas: ");
  //Serial.println(vidas);
  if(luz<=50){
    digitalWrite(buz,HIGH);
    contador();
  }
  else{
    digitalWrite(buz,LOW);
  }
}
