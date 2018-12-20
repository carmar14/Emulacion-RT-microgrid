
#include <DueTimer.h>

//0 es Diesel


//Leave defined if you use native port, comment if using programming port
//#define Serial SerialUSB
//
#define CAN0_TRANSFER_ID    0x05
#define CAN_FRAME_SEND_ID   0x16
#define MAX_CAN_FRAME_DATA_LEN   8

int incomingByte = 0;
int conteo=0;
int i1 = 0, i2 = 0, i3 = 0;
int pb=0, qb=0, pd=0, qd=0;
int pb2,qb2,pd2,qd2;
int flag=0;
//int i3 = 0, vl = 0;
const int ledPin =  LED_BUILTIN;
char aa, tramRasp[26];
String a, spb, spd,sqb, sqd , svl, ssoc;
//String si3;
int pm, qm, vl, soc,vl2;

//volatile boolean pinra = false;
bool pinra=false;
boolean h=false;
bool bi1 = false, bi2 = false,bi3 = false, bi4 = false;
int cont=0;
char frst, scnd, thrd, frth;
//bool v = false, bi3 = false;


void setup()
{
 analogReadResolution(12);
 analogWriteResolution(12);
  Serial.begin(115200);

  pinMode(8, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(9, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(23, LOW);
  digitalWrite(25, LOW);
  digitalWrite(27, LOW);
  digitalWrite(29, LOW);
  digitalWrite(ledPin, LOW);
  conteo=0;
  //attachInterrupt(digitalPinToInterrupt(9), lectura, RISING);

  //delay(2000);
}

void lectura(){
  pinra = true;
 } 

void sendToRasp() {
  
  memset(tramRasp,0,sizeof(tramRasp));
  digitalWrite(27, HIGH);
  sprintf(tramRasp, "fb%07dd%07dp%07de",i1,i2,i3);
    // biomasa, diesel, vl
    //while (pinra == false) {
      //digitalWrite(ledPin,HIGH);
      Serial.println(tramRasp);
      Serial.flush();
      
      //pinra = digitalRead(9);
      //delay(10);
    //}
    //pinra = false;
    //digitalWrite(23, LOW);
    //digitalWrite(25, LOW);
    //digitalWrite(27, LOW);
    //digitalWrite(29, LOW);
    //digitalWrite(ledPin,LOW);
  
}
//void serialEvent() {
void receiveRaspData() {
  //conteo=conteo+1;
  memset(&aa,0,sizeof(aa));
//  while (Serial.available() <= 0) {//Serial.println(2);
//    //delay(1);
//  }
  //digitalWrite(ledPin,LOW);
  //a = "";
  while (Serial.available() > 0) {
    //digitalWrite(ledPin,HIGH);
    aa = Serial.read();  
    a += aa;
    if (aa == '\n') {
      //while(Serial.available()){Serial.read();}
      //digitalWrite(ledPin,HIGH);
      frst = a.charAt(0);
      frth=a.charAt(29);
      
      
      //Serial.println(head);
//      delay(2000);
      //digitalWrite(27,LOW);
      if (frst == 'v' && frth=='e') {
        //Serial.print(a);
        flag=1;
        
        //digitalWrite(ledPin,HIGH);  spb, spd,sqb, sqd 
        spb= a.substring(1, 8);
        
        pb= spb.toInt();

        spd= a.substring(8, 15);
        
        pd= spd.toInt();

        sqb= a.substring(15,22);
        
        qb = sqb.toInt();

        sqd= a.substring(22, 29);
        
        qd = sqd.toInt();
        
        
        //digitalWrite(8, HIGH);
        //digitalWrite(8, LOW);
        //delay(1); // este delay va
//        Serial.println(a);
//        Serial.flush();
        a = "";
      }
      //while( digitalRead(9)!=0);
      Serial.flush();
      a = "";
    }    
  }
  
  //digitalWrite(8, LOW);
  //while(Serial.available()){Serial.read();}
}

void loop() {
 
  //digitalWrite(8, LOW);
  //i1=analogRead(A0);
  //i2=analogRead(A1);
  //i3=analogRead(A2);
  //Serial.println(i1);
  //sendToRasp();
  digitalWrite(8,h);
  h=!h; 
  receiveRaspData();
  
  pd2=map(pb, 0, 50000, 0, 4095);
  qd2=map(qb, 0, 50000, 0, 4095);
  //vl2=map(vl, -3500, 3500, 0, 4095);pb2,qb2,pd2,qd2;
  //vl=map(vl, -500, 700, 0, 4095);
  
  //vl2=map(vl, -1000, 1000, 0, 4095);
  
  analogWrite(DAC0,pd2);
  analogWrite(DAC1,qd2);
  //analogWrite(DAC0,2000);
  //digitalWrite(27, LOW);
  
  
  //digitalWrite(27, LOW);
  //cont=cont+1;
  //while( cont==3){}
  /*if(conteo==1050){
    digitalWrite(ledPin,HIGH);
  }*/
  delay(13);
}
