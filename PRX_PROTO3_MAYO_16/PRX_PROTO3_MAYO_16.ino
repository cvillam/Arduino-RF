/**
 * PROGRAMA RECEPTOR
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 */
 
 // modificacion de archivos bla bla

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
byte modo;
byte pin;
byte accion;
byte ok = 111;
boolean pinver=false;
int led1 = 2;
int led2= 3;
int lightPin = 0;
int lectura;


void setup(){
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  Serial.begin(9600);
   Mirf.spi = &MirfHardwareSpi;
   Mirf.init();
  //Configurar direccion recepcion.
   Mirf.setRADDR((byte *)"txaddr");
  //Configurar direccion transmision.
   Mirf.setTADDR((byte *)"rxaddr");
  //Se fija el tamaño del Payload, debe ser el mismo en TX y RX
   Mirf.payload = 1;
  //Se configura canal de TX, debe ser el mismo en TX y RX
   Mirf.channel = 90;
   Mirf.config();
  delay(50);

}

void loop(){
       Mirf.setTADDR((byte *)"rxaddr");
     Mirf.setRADDR((byte *)"txaddr");
     Mirf.config();
      while(Mirf.dataReady()==false){}
      if(Mirf.dataReady()){
         Mirf.getData((byte*)&modo);
         if(modo==113){
            ModEstado();
        }
      }
      delay(50);      
  }
void ModEstado(){
     Mirf.setTADDR((byte *)"rxaddr");
     Mirf.setRADDR((byte *)"txaddr");
     Mirf.config();
     while(Mirf.dataReady()==false){}
        if(Mirf.dataReady()){
          Mirf.getData((byte*)&pin);
              
              if(pin==50){
                  if(digitalRead(led1)==HIGH){
                      digitalWrite(led1, LOW);
                      Mirf.send((byte *)"o");
                     while(Mirf.isSending()){}
                       delay(50);
                  }
                  else{
                    digitalWrite(led1,HIGH);
                    Mirf.send((byte *)"o");
                     while(Mirf.isSending()){}
                       delay(50);
                  }
              }
              else if(pin==51){
                  if(digitalRead(led2)==HIGH){
                      digitalWrite(led2, LOW);
                      Mirf.send((byte *)"o");
                     while(Mirf.isSending()){}
                       delay(50);
                  }
                  else{
                    digitalWrite(led2,HIGH);
                    Mirf.send((byte *)"o");
                     while(Mirf.isSending()){}
                       delay(50);
                  }
              }
              
              
          }

}  
  
  
  
 
