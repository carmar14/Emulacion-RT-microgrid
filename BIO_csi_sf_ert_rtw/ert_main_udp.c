/* compile using  "gcc ert_main_udp.c BIO_csi_sf.c rt_nonfinite.c rtGetInf.c rtGetNaN.c libmcp3204.c -lm -lwiringPi -lrt -Wall"  */
//
/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'BIO_csi_sf'.
 *
 * Model version                  : 1.63
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Aug 14 16:25:22 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "BIO_csi_sf.h"                /* Model's header file */
#include "rtwtypes.h"
#include <wiringSerial.h>
#include <stdlib.h> 
#include <errno.h>
#include <string.h>
#include <unistd.h> 
#include <termios.h>
#include <wiringPi.h>
#include <ncurses.h>
#include "libmcp3204.h"

//-------------------Comunicacion UDP--------------------------------------
//-----------------Direcciones IP-----

#define SERVER "172.16.49.101"   //Direcion IP del Inversor
#define PORTL 8887			//Puerto Local
#define PORTR1 8886			//Puerto Remoto I1
#define PORTR2 8885			//Puerto Remoto Duty



//===============================================================
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
//===============================================================

//===============================================================
void die(char *);
void setUDP(void);
double receive (void);
void sendm(double);
//===============================================================

//===============================================================
struct sockaddr_in si_me, si_other, si_other2; //
int BUFLEN=512;
int s, slen = sizeof(si_other) , recv_len;
char buf[512];
double duty_cycle=0.0;
//===============================================================

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
 
 //Variables creadas por el programador
 
 //------Entradas-------
 double vdc=0.0;
 double vload=0.0;
 double pref=0.0;
 double qref=0.0;
 MCP3204 ad_MCP3204;
 int fileDescriptor;
 char error[55];
 double vcarga=0.0;
 double tiempo=0.0;
	 
 //------Salidas--------
 double i1=0.0;
 
 
 #define MSGISIZE 9
 
 //Comunicacion
 int  bytes_read = 0; 
 int pinr=0;
  int var=0;
  char bufferAux;
  char read_buffer[MSGISIZE];   /* Buffer to store the data received              */
  int var1=0;
 int var2=0;
 int var3=0;
 char var1s[7];
 char var2s[7];
 char var3s[7];
 int fd;
 int i1a=0;
 char buffer[8];
 
  //===============================================================
 //-------Variables para graficar
 #include <math.h>
 #define NUM_POINTS 100000
 char * commandsForGnuplot[] = {"set title \"TITLEEEEE\"", "plot 'data.temp'"};
 double xvals[NUM_POINTS];//= {1.0, 2.0, 3.0, 4.0, 5.0};
 double yvals[NUM_POINTS];// = {5.0 ,3.0, 1.0, 3.0, 5.0};
 FILE * temp;
 FILE *	gnuplotPipe;
 double in=0;
 //===============================================================
 //--------------Para RT-----------------
#include <time.h>
#include <sched.h>
//#include <wiringPi.h>

#define NSEC_PER_SEC    1000000000

//--------------------------------------
 
 
void rt_OneStep(void);

//----------------------------Para RT------------------------------
/* using clock_nanosleep of librt */
extern int clock_nanosleep(clockid_t __clock_id, int __flags,
      __const struct timespec *__req,
      struct timespec *__rem);

/* the struct timespec consists of nanoseconds
 * and seconds. if the nanoseconds are getting
 * bigger than 1000000000 (= 1 second) the
 * variable containing seconds has to be
 * incremented and the nanoseconds decremented
 * by 1000000000.
 */
static inline void tsnorm(struct timespec *ts)
{
   while (ts->tv_nsec >= NSEC_PER_SEC) {
      ts->tv_nsec -= NSEC_PER_SEC;
      ts->tv_sec++;
   }
}

//====================Para UDP-TCP==========================
void die(char *s)
{
    perror(s);
    exit(1);
}

void setUDP(void)
{
	
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
    
    //Setting timeout for socket for 1ms
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
		perror("Error");
	}
     
    // zero out the structure
    memset((char *) &si_other, 0, sizeof(si_other));
     
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORTR);
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
    
     memset((char *) &si_other2, 0, sizeof(si_other2));
    
    si_other2.sin_family = AF_INET;
    si_other2.sin_port = htons(PORTR2);
    if (inet_aton(SERVER , &si_other2.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
		
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORTL);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//bind socket to port
	//Crea socket para MPC
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind s1");
    }
}

double receive (void)
{
	double x = 1.0;
	printf("Waiting for data...");
	memset(buf,'\0', BUFLEN);

	//try to receive some data, this is a blocking call
	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) < 0)
	{
		printf("Timeout o fallo de recepción\n");
		x=-1.0;
		return x;
		//die("recvfrom()");
	}
	
	//Para llegar aca tuvo que haber recepción exitosa desde inversor
	sendm(vdcmdiesel);
	/*memset(buf,'\0', BUFLEN);
	sprintf(buf, "%5.2f", vdcmdiesel);
	printf("Dato a enviar: %s\n",buf);
	
	if (sendto(s, buf, BUFLEN, 0, (struct sockaddr*) &si_other, slen) == -1)
	{
		die("sendto()");
	}
	*/
	
	return x;
}

void sendm1(double mensaje)
{
    memset(buf,'\0', BUFLEN);
    sprintf(buf, "%5.2f", mensaje);
    printf("Dato a enviar: %s\n",buf);
    
    //print details of the client/peer and the data received
    //printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
    //printf("Data: %s\n" , buf);
    //printf("Numeric Data %3.2f\n",x);
    //now reply the client with the same data
    if (sendto(s, buf, BUFLEN, 0, (struct sockaddr*) &si_other, slen) == -1)
    {
        die("sendto()");
    }
    
}

void sendm2(double mensaje)
{
    memset(buf,'\0', BUFLEN);
    sprintf(buf, "%5.2f", mensaje);
    printf("Dato a enviar: %s\n",buf);

    if (sendto(s, buf, BUFLEN, 0, (struct sockaddr*) &si_other2, slen) == -1)
    {
        die("sendto()");
    }
    
}

//===============================================================
//------------------------------------------------------------------

void rt_OneStep(void)
{
  //digitalWrite(21,HIGH);
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(BIO_csi_sf_M, "Overrun");
    return;
  }

  OverrunFlag = true;
  

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  //------Entradas-------
  
  //digitalWrite(21,LOW);
  /*
  tcflush(fd, TCIOFLUSH);
  var=0;
  //(read_buffer,0,sizeof(read_buffer));
  //printf("Va leer 2\n");
  memset(&bufferAux,0,sizeof(bufferAux));
  //printf("Va leer\n");
  //sprintf(read_buffer,"b%07dd%07de\n",Pma,Qma);
  while(serialDataAvail(fd)==0){} 
  
  memset(read_buffer,0,sizeof(read_buffer));
  //printf("Captó dato serial\n");
  //Nuevooooooooo
  while(read_buffer[0]!='f' || read_buffer[MSGISIZE-1]!='e'){
  bytes_read=read(fd,&read_buffer,MSGISIZE); 
  serialFlush(fd);
  tcflush(fd, TCIOFLUSH);
  }
  
  //Nuevoooooo
  digitalWrite(0,HIGH);
  serialFlush(fd);
  tcflush(fd, TCIOFLUSH);*/
  
  var=1;
  
  if (MCP3204_convert(fileDescriptor,singleEnded,CH0,&ad_MCP3204,error))
	{
		printf("Error during conversion1.\n");
		printf("%s\n",error);
		exit(1);
	}
	
	
	var1=MCP3204_getValue(ad_MCP3204);
	
	if (MCP3204_convert(fileDescriptor,singleEnded,CH1,&ad_MCP3204,error))
	{
		printf("Error during conversion1.\n");
		printf("%s\n",error);
		exit(1);
	}
	
	
	var2=MCP3204_getValue(ad_MCP3204);
	
	if (MCP3204_convert(fileDescriptor,singleEnded,CH2,&ad_MCP3204,error))
	{
		printf("Error during conversion1.\n");
		printf("%s\n",error);
		exit(1);
	}
	
	
	var3=MCP3204_getValue(ad_MCP3204);
	
	//printf("Digital value of the sensor reading: %d\n",var1);
  
  //printf("Trama de arduino: %s\n",read_buffer);
  
  /*if (var==1){
	  int q=0;
	  //Acomodar en arreglo de caracteres los datos recibidos
	  for(q=0; q<7;q++){
		var1s[q]=read_buffer[q+1]; //Primer dato
		//var2s[q]=read_buffer[q+10]; //Segundo dato
		//var3s[q]=read_buffer[q+18]; //Tercer dato
      }
  var1=atoi(var1s);//Primer dato en numero*/
  
  //var2=atof(var2s)/10.0; //Segundo dato en numero
  //var3=atof(var3s)/10.0; //Segundo dato en numero
  
  //var3=atof(var3s)/10.0; //Segundo dato en numero    
  //printf ("El numero1  es :%d \n",var1);
  //printf ("El numero2  es :%3.2f \n",var2); 
  //printf ("El numero3  es :%3.2f \n",var3);
  //double k=(2220+2150)/4095;
  //double vx=-2150;
  //double k=(2300+2300)/4095;
  //double vx=-2300;
  double k=(2*170)/2248.0;
  double vx=-170-(502*2*170)/2248.0;
  double k2=0.5;
  double vx2=-0.5*500;
  double k3=2.0;
  double vx3=-2*500.0;
  
  vdc=500;   //Proveniente de la fuente de generación
  //vload=171*sin(2*3.14*120*tiempo);//var1*k+vx; //Proveniente de la carga
  vload=var1*k+vx; 
  tiempo=tiempo+0.0001;
  //if (tiempo>=0.0167) tiempo=0;
  if (tiempo>=0.0083) tiempo=0;
  //vload=vload/10.0;
  //pref=100.0;//var2*k2+vx2;//500.0;  //Proveniente del control terciario
  //qref=1000.0;//var3*k3+vx3;//3500.0; //Proveniente del control terciario
  
  pref=var2*k2+vx2;//500.0;  //Proveniente del control terciario
  qref=var3*k3+vx3;
  //pref=500;
  //qref=3500;
  
  set_Vdc_bio(vdc);
  set_Vload(vload);
  set_Qref_bio(qref);
  set_Pref_bio(pref);

  /* Step the model for base rate */
  BIO_csi_sf_step();
   

  /* Get model outputs here */
  //------Salidas--------
  i1=get_I_bio();
  duty_cycle=get_duty();
  double mpc1=get_MPC1();
  printf("El vload es : %3.2f \n",vload);
  printf("La potencia P es: %3.2f \n",pref);
  printf("La potencia Q es: %3.2f \n", qref);
  printf("La corriente del inversor 1 es: %3.2f \n",i1);
  printf("La accion de control 1 del mpc  es: %3.2f \n", mpc1);
  
  
  //-------------UDP-envio----------------------
  sendm1(i1);
  sendm2(duty_cycle);
  
  
  //----------Serial----------------------
  //-----------Escritura-envio---------------------
  //Pma=Pm*10;
  //Qma=Qm*10;
  i1a=i1*10;
  //if(i1a>1500){
	  //i1a=1500;
  //}else if(i1a<-1500){
	  //i1a=-1500;
  //}
  
  memset(buffer,0,sizeof(buffer));
   //sprintf(buffer,"p%07dq%07dv%07ds%07d\n",Pma,Qma,Vloada,soca);
   sprintf(buffer,"v%07d\n",i1a);
  //printf("%s",buffer);
   //while(pinr==0){
	   serialPuts(fd,buffer);
	   serialFlush(fd);
	   //pinr=digitalRead(2);
	   //printf("El dato pin es: %d \n",pinr);
   //}
   serialFlush(fd);
   tcflush(fd, TCIOFLUSH);
   pinr=0;
   
   var=0;
   
   //-----------Grafica---------------------
   //in+=0.0001;
   fprintf(temp, "%3.2f %3.2f %3.2f \n", mpc1,vload,i1);
  //}


  /* Indicate task complete */
  OverrunFlag = false;
  //digitalWrite(21,LOW);

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
	//Para RT
  struct timespec t;
  struct sched_param param;
  /* default interval = 50000ns = 50us
   * cycle duration = 100us
   */
   
  printf("Iniciando \n");
   
  int interval=4*1000000;		//en ns   ->  20000=20us
  
	if(argc>=2 && atoi(argv[1])>0)
   {
      printf("using realtime, priority: %d\n",atoi(argv[1]));
      param.sched_priority = atoi(argv[1]);
      /* enable realtime fifo scheduling */
      if(sched_setscheduler(0, SCHED_FIFO, &param)==-1){
         perror("sched_setscheduler failed");
         exit(-1);
      }
   }
   if(argc>=3){
      interval=atoi(argv[2]);
      printf("using realtime, priority: %d\n",interval);
	}
   
   
  /* Unused arguments */
  (void)(argc);
  (void)(argv);
  
  
  
  //Grafica
  
  
  temp = fopen("data.temp", "w");
    
   gnuplotPipe = popen ("gnuplot -persistent", "w");
    
  fprintf(gnuplotPipe,"set grid \n");
  
  //Serial
  
  fd=serialOpen ("/dev/ttyACM0", 115200);
  serialClose(fd);
  fd=serialOpen ("/dev/ttyACM0", 115200);
  
  sleep(1);
  
  //Inicializar comunicacion UDP---------------------------------------------------------
  setUDP();
  
   //------------GPIO---------------------
  wiringPiSetup();
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(21, OUTPUT);
  //wiringPiISR(2, INT_EDGE_RISING, &lectura);
  pinMode(2, INPUT);
  digitalWrite(3,HIGH);
  digitalWrite(1,LOW);
  
  if (MCP3204_init(&fileDescriptor,"/dev/spidev1.2",&ad_MCP3204,mode_SPI_00,4.08,error))
		{
			printf("Cannot initialize the MCP3204 ADC.\n");
			printf("%s\n",error);
			exit(1);
		}

  /* Initialize model */
  
  BIO_csi_sf_initialize();
  int k=0;
  int estado=0;
  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
   
  /* get current time */
   clock_gettime(0,&t);
   /* start after one second */
   t.tv_sec++;
   
  while ((rtmGetErrorStatus(BIO_csi_sf_M) == (NULL)) && !rtmGetStopRequested
         (BIO_csi_sf_M)) {
			 
	/* wait untill next shot */
    clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
    /* do the stuff */
    if(estado==0){
	   estado=1;
	   
   }else{
	   estado=0; 
   }
   digitalWrite (21, estado) ; 
    rt_OneStep();
    t.tv_nsec+=interval;
    tsnorm(&t);
    //sleep(1);
    //delayMicroseconds(3000);
    //k++;
	//if(k==30000){
		//break;
	//}
	
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  BIO_csi_sf_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
