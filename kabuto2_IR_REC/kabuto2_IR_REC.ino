/*Projeto Kabuto 2
Vitor Domingues
https://github.com/vitorshaft/kabuto
*/
//IR transmissor: tem 2 pinos (transparente)
//IR receptor: tem 3 pinos (escuro)
#include <SoftwareSerial.h>
#define TX 13
#define RX 8 //PINO ANALÓGICO UTILIZADO PELO FOTOTRANSISTOR



void setup(){
  Serial.begin(9600); //INICIALIZAÇÃO DA SERIAL
  pinMode(pinoFototransistor, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(TX, OUTPUT);
  digitalWrite(TX, HIGH); //transmissor ligado direto
}

void loop(){
//  if(analogRead(pinoFototransistor) < 800){ //SE A LEITURA DO PINO FOR MENOR QUE 800 BITS, FAZ
//    Serial.println("Recebendo sinal infravermelho"); //IMPRIME O TEXTO NA SERIAL
//  }else{ //SENÃO, FAZ
//    Serial.println("Sinal infravermelho interrompido"); //IMPRIME O TEXTO NA SERIAL
//  }
Serial.println(analogRead(pinoFototransistor));

 }
