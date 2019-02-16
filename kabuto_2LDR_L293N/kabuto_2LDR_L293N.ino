/*Sketch made on 15-February-2019
 * Vitor Domingues
 * vitordomingues@ymail.com
 * https://sites.google.com/view/vitordomingues
 * This sketch was developed for Arduino robot using L298N H-Bridge.
 * If your Robot uses IC ULN2003 please refer to kabuto_laser_ULN2003.ino file
 */
int buz = 5;  //digital pin for buzzer
int LDR = A0; //LDR made as target (back of the robot)
int LDR2 = A1;  //LDR2 is the ambient light sensor to be compared with the target LDR
int LDR_alvo;
int LDR_ambiente;
int vidas = 3; //total of lives

void contador(){
  //int freq = 264;
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
  LDR_alvo = analogRead(LDR);
  LDR_ambiente = analogRead(LDR2);    //Darker = higher value; Lighter = lower value.
  int ganho = LDR_ambiente - LDR_alvo;  //"ganho" is "gain" in portuguese and means the difference between the LDRs
  Serial.println(ganho);
  if(ganho > 200){          //normally 1 meter at night
    contador();
  }
  else{
    digitalWrite(buz,LOW);
  }
  if(Serial.available()){       //check if the module is receiving anything via bluetooth
    int recebe = Serial.read(); //"recebe" is portuguese for "receive"
    int valor = recebe-48;
    Serial.println(valor);     //show on Serial Monitor the value received via bluetooth
    if(valor==1){         //The value is added on 48 units because of the ASCII table
      digitalWrite(13,HIGH);    //turns on the laser attached to pin 13 (change 13 to any other pin number if you want)
      tone(buz, 880);
    }
    else if(valor==0){    //if the received value is 0...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      noTone(buz);
      digitalWrite(9,LOW);      //de-activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);      //de-activates motor B
      digitalWrite(12,LOW);
      
    }
    else if(valor==54){    //if the received value is 54...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      noTone(buz);
      digitalWrite(9,HIGH);      //activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);     //activates motor B
      digitalWrite(12,HIGH);
    }
    else if(valor==52){    //if the received value is 52...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      noTone(buz);
      digitalWrite(9,HIGH);      //activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);     //de-activates motor B
      digitalWrite(12,LOW);
    }
    else if(valor==53){    //if the received value is 53...
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      noTone(buz);
      digitalWrite(9,LOW);      //de-activates motor A
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);     //activates motor B
      digitalWrite(12,HIGH);
    }
    else if(valor==68){
      digitalWrite(13,LOW);     //turns off the laser attached to pin 13
      noTone(buz);
      digitalWrite(9,LOW);      //activates motor A
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);     //activates motor B
      digitalWrite(12,LOW);
    }
    
  }
}
