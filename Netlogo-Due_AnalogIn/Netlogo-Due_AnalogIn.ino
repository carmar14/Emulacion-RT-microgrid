//ttYacm0
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int incomingByte = 0;
int i1 = 0, i2 = 0, i3 = 0;
int pb=0, qb=0, pd=0, qd=0;
int flag=0;
//int i3 = 0, vl = 0;
const int ledPin =  LED_BUILTIN;
char aa, tramRasp[9];
String a, spm, sqm, svl, ssoc;
//String si3;
int pm, qm, vl,vl2, soc;

//volatile boolean pinra = false;
bool pinra=false;
bool bi1 = false, bi2 = false,bi3 = false, bi4 = false;
int cont=0;
char frst, scnd, thrd, frth;


void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  SerialUSB.begin(9600);
}


void receiveRaspData() {
  memset(&aa,0,sizeof(aa));

  while (Serial.available() > 0) {
    //digitalWrite(ledPin,HIGH);
    aa = Serial.read();  
    a += aa;
    if (aa == '\n') {
      
      frst = a.charAt(0);
      

      if (frst == 'v') {
        //Serial.print(a);
        flag=1;
        
        //digitalWrite(ledPin,HIGH);
        svl= a.substring(1, 8);
        
        vl = svl.toInt();
        
        digitalWrite(8, HIGH);
        digitalWrite(8, LOW);

        a = "";
      }
      //while( digitalRead(9)!=0);
      Serial.flush();
      a = "";
    }    
  }
}



void loop() {
  // read the value from the sensor:
  receiveRaspData();
  sensorValue = analogRead(sensorPin);
  sensorValue=map(sensorValue,0,1024,0,50);
  SerialUSB.print("C,");
  SerialUSB.print(vl);
  SerialUSB.print(";");
}
