/*Sketch made on 13-December-2018
 * Vitor Domingues
 * vitordomingues@ymail.com
 * https://sites.google.com/view/vitordomingues
 * This sketch was developed for Arduino robot using ULN2003 IC as H-Bridge.
 * If your Robot uses L293 or L298 H-Bridge please refer to *_laser_robot_L29X.ino file
 */
int buz = 5;
int LDR = A0;
int valor = 0;
int vidas = 3;

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
  pinMode(LDR, INPUT); //define LDR liht sensor (pin A0) as input
 
  pinMode(13,OUTPUT); //define pin 13 (laser) as output
  pinMode(9, OUTPUT); //define pin 9 (motor A) as output
  pinMode(10,OUTPUT); //define pin 10 (motor A) as output
  pinMode(11, OUTPUT); //define pin 11 (motor B) as output
  pinMode(12,OUTPUT); //define pin 12 (motor B) as output
  Serial.begin(9600); //Start Serial Communication (bluetooth)

  digitalWrite(9,LOW);      //de-activates motor A
  digitalWrite(10,LOW);     //de-activates motor A
  digitalWrite(11,LOW);      //de-activates motor B
  digitalWrite(12,LOW);     //de-activates motor B
}

void loop() {
  valor = analogRead(LDR);
  if(valor<=500){
    contador();
  }
  else{
    digitalWrite(buz,LOW);
  }
  if(Serial.available()){       //check if the module is receiving anything via bluetooth
    int recebe = Serial.read(); //"recebe" is portuguese for "receive"
    int valor = recebe-48;
    Serial.println(valor);     //show on Serial Monitor the value received via bluetooth
    if(valor==1){         //The value is added on 48 units because of the comms protocol
      digitalWrite(13,HIGH);    //turns on the laser attached to pin 13 (change 13 to any other pin number if you want)
    }
    else if(valor==0){    //if the received value is 0...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,LOW);      //de-activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);      //de-activates motor B
      digitalWrite(12,LOW);
      
    }
    else if(valor==54){    //if the received value is 54...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,HIGH);      //activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);     //activates motor B
      digitalWrite(12,HIGH);
    }
    else if(valor==52){    //if the received value is 52...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      digitalWrite(9,HIGH);      //activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);     //de-activates motor B
      digitalWrite(12,LOW);
    }
    else if(valor==53){    //if the received value is 53...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
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
