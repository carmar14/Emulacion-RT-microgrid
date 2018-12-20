// compile with: "gcc ert_main.c PV_vsi_sf.c PV_vsi_sf_data.c BIO_csi_sf.c Diesel_csi_sf.c rt_nonfinite.c rtGetInf.c rtGetNaN.c libmcp3204.c  -lm -lwiringPi -lrt -Wall -lpthread"
/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'Diesel_csi_sf'.
 *
 * Model version                  : 1.70
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Aug 15 11:30:36 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "Diesel_csi_sf.h"             /* Model's header file */
#include "BIO_csi_sf.h" 
#include "PV_vsi_sf.h"                 /* Model's header file */
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
 
 //Variables  PV
 //------Entradas-------
 double ipv=0.0;
 double vload3=0.0;
 MCP3204 ad_MCP3204;
 int fileDescriptor;
 char error[55];

 //------Salidas--------
 double i3=0.0;
 double soc=0.0;
 int fd3;
 int i3a=0;
 char buffer3[8];
 
 
 //Variables BIO
 
 double vdc=0.0;
 double vload=0.0;
 double pref=0.0;
 double qref=0.0;
 //MCP3204 ad_MCP3204;
 //int fileDescriptor;
 //char error[55];
 double vcarga=0.0;
 double tiempo=0.0;
	 
 //------Salidas--------
 double i1=0.0;
  int i1a=0;
 
  char buffer2[8];
  int fd2;
 
 
 //Variables creadas por el programador Diesel
 //------Entradas-------
 double Pref_d=0.0;
 double Qref_d=0.0;
 double Vload=0.0;
 double par=0.0;
 double flujo=0.0;
 MCP3204 ad_MCP3204;
 int fileDescriptor;
 char error[55];

 //------Salidas--------
 double Idie=0.0;
 double min=5000;
 double max=0.0;
 
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
 int i2a=0;
 char buffer[8];
 
  //===============================================================
 //-------Variables para graficar
 #include <math.h>
 #define NUM_POINTS 100000
 char * commandsForGnuplot[] = {"set title \"TITLEEEEE\"", "plot 'data.temp'"};
 double xvals[NUM_POINTS];//= {1.0, 2.0, 3.0, 4.0, 5.0};
 double yvals[NUM_POINTS];// = {5.0 ,3.0, 1.0, 3.0, 5.0};
 FILE * temp;
 FILE * temp2;
 FILE * temp3;
 FILE *	gnuplotPipe;
 double in=0;
 //===============================================================
 
 //--------------Para RT-----------------
#include <time.h>
#include <sched.h>
#include <pthread.h>
#include <semaphore.h>
//#include <wiringPi.h>
sem_t low_go, mid_go, high_go, high_ready, mid_ready;
pthread_mutex_t shared_mutex;
const int minutes = 60;
const int seconds = 1;
pthread_mutexattr_t mutex_attr;

#define LOW_SPIN 2
#define MID_SPIN 5

#define NSEC_PER_SEC    1000000000

//--------------------------------------
 
 
void *rt_OneStep_Diesel(void *n);
void *rt_OneStep_Bio(void *n);
void *rt_OneStep_PV(void *n);

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
//------------------------------------------------------------------
int gettime ()
{
  return time(NULL);
}


void *rt_OneStep_Diesel(void *n)
{
    struct sched_param the_priority;
	int estado=0;
	/* default interval = 50000ns = 50us
	* cycle duration = 100us
	*/
	int interval=4*1000000;		//en ns   ->  20000=20us
	struct timespec t;
	//struct sched_param param;
	
	//~ if (wiringPiSetup () == -1)
		//~ return NULL;
	//~ pinMode (3, OUTPUT) ;  
	
    the_priority.sched_priority  = 50;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &the_priority);

	temp = fopen("data.temp", "w");
    gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe,"set grid \n");
  
  //Serial
  
    fd=serialOpen ("/dev/ttyACM0", 115200);
    serialClose(fd);
	fd=serialOpen ("/dev/ttyACM0", 115200);
    
	sleep(1);
    
    //------------GPIO---------------------
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    //wiringPiISR(2, INT_EDGE_RISING, &lectura);
    pinMode(2, INPUT);
    digitalWrite(3,HIGH);
    digitalWrite(1,LOW);
    
    
    /* Initialize model */
    Diesel_csi_sf_initialize();
    
    /* get current time */
    clock_gettime(0,&t);
    /* start after one second */
    t.tv_sec++;
	
while ((rtmGetErrorStatus(Diesel_csi_sf_M) == (NULL)) && !rtmGetStopRequested
	(Diesel_csi_sf_M)) {
	
	/* wait untill next shot */
	clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
	/* do the stuff */
	if(estado==0){
	estado=1;
	
	}else{
	estado=0; 
	}
	digitalWrite (21, estado) ; 
		 
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(Diesel_csi_sf_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */
  //-------entradas-------------
  digitalWrite(0,LOW);
  /*tcflush(fd, TCIOFLUSH);
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
  while(read_buffer[0]!='f' && read_buffer[MSGISIZE-1]!='e'){
  bytes_read=read(fd,&read_buffer,MSGISIZE); 
  serialFlush(fd);
  tcflush(fd, TCIOFLUSH);
  }
   
  //Nuevoooooo
  digitalWrite(0,HIGH);
  serialFlush(fd);
  tcflush(fd, TCIOFLUSH);
  */
  var=1;
  
  if (MCP3204_convert(fileDescriptor,singleEnded,CH0,&ad_MCP3204,error))
	{
		printf("Error during conversion1.\n");
		printf("%s\n",error);
		exit(1);
	}
	
	
	var1=MCP3204_getValue(ad_MCP3204);
  
  //printf("Trama de arduino: %s\n",read_buffer);
  
  /*if (var==1){
	  int q=0;
	  //Acomodar en arreglo de caracteres los datos recibidos
	  for(q=0; q<7;q++){
		var1s[q]=read_buffer[q+1]; //Primer dato
		//var2s[q]=read_buffer[q+10]; //Segundo dato
		//var3s[q]=read_buffer[q+18]; //Tercer dato
      }
  var1=atoi(var1s);//Primer dato en numero
  //var2=atof(var2s)/10.0; //Segundo dato en numero
  //var3=atof(var3s)/10.0; //Segundo dato en numero
  
  //var3=atof(var3s)/10.0; //Segundo dato en numero    
  //printf ("El numero1  es :%d \n",var1);
  //printf ("El numero2  es :%3.2f \n",var2); 
  //printf ("El numero3  es :%3.2f \n",var3);
  */
  
  double k=(2*170)/2248.0;
  double vx=-170-(502*2*170)/2248.0;
  //double k=(2220+2150)/4095;
  //double vx=-2150;
  
  Pref_d=100.0;//100.0;//500.0;
  Qref_d=1000.0;//1500.0;//3500;
  Vload=var1*k+vx;
  //Vload=Vload/10.0;
  par=1.4;
  flujo=1;
  
  set_Pref_d(Pref_d);
  set_Qref_d(Qref_d);
  set_Vload(Vload);
  set_par(par);
  set_flujo(flujo);

  /* Step the model for base rate */
  Diesel_csi_sf_step();

  /* Get model outputs here */
  //-----salidas-------
  Idie=get_I_die();
  printf("La corriente del inversor 2 es: %3.2f \n",Idie);
  printf("La tension es : %3.2f \n",Vload);
  if (min>Idie) min=Idie;
  if (max<Idie) max=Idie;
	
	printf("Valor minimo: %3.2f \n", min);
	printf("Valor maximo: %3.2f \n", max);
  
  //----------Serial----------------------
  //-----------Escritura-envio---------------------
  //Pma=Pm*10;
  //Qma=Qm*10;
  i2a=Idie*10; 
  
  memset(buffer,0,sizeof(buffer));
   //sprintf(buffer,"p%07dq%07dv%07ds%07d\n",Pma,Qma,Vloada,soca);
   sprintf(buffer,"v%07d\n",i2a);
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
   //fprintf(temp, "%3.2f %3.2f %3.2f %3.2f %3.2f %3.2f \n",i1,i2,i3,Vload,Pm,Qm);
   fprintf(temp, "%3.2f %3.2f \n",Idie,Vload);
  //}

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
  t.tv_nsec+=interval;
  tsnorm(&t);
  }
  Diesel_csi_sf_terminate();
}


void *rt_OneStep_Bio(void *n)
{
    struct sched_param the_priority;
	/* default interval = 50000ns = 50us
	* cycle duration = 100us
	*/
	int interval=4*1000000;		//en ns   ->  20000=20us
	struct timespec t;
	//struct sched_param param;
	
	//~ if (wiringPiSetup () == -1)
		//~ return NULL;
	//~ pinMode (3, OUTPUT) ;  
	
    the_priority.sched_priority  = 49;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &the_priority);

	temp2 = fopen("data2.temp", "w");
    gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe,"set grid \n");
  
  //Serial
  
    fd2=serialOpen ("/dev/ttyACM1", 115200);
    serialClose(fd2);
	fd2=serialOpen ("/dev/ttyACM1", 115200);
    
	sleep(1);
    
    //------------GPIO---------------------
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    //wiringPiISR(2, INT_EDGE_RISING, &lectura);
    pinMode(2, INPUT);
    digitalWrite(3,HIGH);
    digitalWrite(1,LOW);
    
    
    /* Initialize model */
    BIO_csi_sf_initialize();
    
    /* get current time */
    clock_gettime(0,&t);
    /* start after one second */
    t.tv_sec++;
	
while ((rtmGetErrorStatus(BIO_csi_sf_M) == (NULL)) && !rtmGetStopRequested
         (BIO_csi_sf_M)) {
	
	/* wait untill next shot */
	clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
	/* do the stuff */
	//if(estado==0){
	//estado=1;
	
	//}else{
	//estado=0; 
	//}
	//digitalWrite (21, estado) ; 
		 
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
  
  if (MCP3204_convert(fileDescriptor,singleEnded,CH1,&ad_MCP3204,error))
	{
		printf("Error during conversion1.\n");
		printf("%s\n",error);
		exit(1);
	}
	
	
	var2=MCP3204_getValue(ad_MCP3204);
	
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
  
  vdc=500;   //Proveniente de la fuente de generación
  //vload=171*sin(2*3.14*120*tiempo);//var1*k+vx; //Proveniente de la carga
  vload=var2*k+vx; 
  tiempo=tiempo+0.0001;
  //if (tiempo>=0.0167) tiempo=0;
  if (tiempo>=0.0083) tiempo=0;
  //vload=vload/10.0;
  pref=100.0;//100.0;//500.0;  //Proveniente del control terciario
  qref=1000.0;//1500.0;//3500.0; //Proveniente del control terciario
  
  set_Vdc_bio(vdc);
  set_Vload2(vload);
  set_Qref_bio(pref);
  set_Pref_bio(qref);

  /* Step the model for base rate */
  BIO_csi_sf_step();
   

  /* Get model outputs here */
  //------Salidas--------
  i1=get_I_bio();
  double mpc1=get_MPC1();
  printf("El vload es : %3.2f \n",vload);
  printf("La corriente del inversor 1 es: %3.2f \n",i1);
  printf("La accion de control 1 del mpc  es: %3.2f \n", mpc1);
  
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
  
  memset(buffer2,0,sizeof(buffer2));
   //sprintf(buffer,"p%07dq%07dv%07ds%07d\n",Pma,Qma,Vloada,soca);
   sprintf(buffer2,"v%07d\n",i1a);
  //printf("%s",buffer);
   //while(pinr==0){
	   serialPuts(fd2,buffer2);
	   serialFlush(fd2);
	   //pinr=digitalRead(2);
	   //printf("El dato pin es: %d \n",pinr);
   //}
   serialFlush(fd2);
   tcflush(fd2, TCIOFLUSH);
   pinr=0;
   
   var=0;
   
   //-----------Grafica---------------------
   //in+=0.0001;
   fprintf(temp2, "%3.2f %3.2f %3.2f \n", mpc1,vload,i1);
  //}


  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
  t.tv_nsec+=interval;
  tsnorm(&t);
  }
  Diesel_csi_sf_terminate();
}


void *rt_OneStep_PV(void *n)
{
    struct sched_param the_priority;
	/* default interval = 50000ns = 50us
	* cycle duration = 100us
	*/
	int interval=4*1000000;		//en ns   ->  20000=20us
	struct timespec t;
	//struct sched_param param;
	
	//~ if (wiringPiSetup () == -1)
		//~ return NULL;
	//~ pinMode (3, OUTPUT) ;  
	
    the_priority.sched_priority  = 51;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &the_priority);

	temp3 = fopen("data3.temp", "w");
    gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(gnuplotPipe,"set grid \n");
  
  //Serial
  
    fd3=serialOpen ("/dev/ttyACM1", 115200);
    serialClose(fd3);
	fd3=serialOpen ("/dev/ttyACM1", 115200);
    
	sleep(1);
    
    //------------GPIO---------------------
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    //wiringPiISR(2, INT_EDGE_RISING, &lectura);
    pinMode(2, INPUT);
    digitalWrite(3,HIGH);
    digitalWrite(1,LOW);
    
    
    /* Initialize model */
    PV_vsi_sf_initialize();
    
    /* get current time */
    clock_gettime(0,&t);
    /* start after one second */
    t.tv_sec++;
	
while ((rtmGetErrorStatus(PV_vsi_sf_M) == (NULL)) && !rtmGetStopRequested
         (PV_vsi_sf_M)) {
	
	/* wait untill next shot */
	clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
	/* do the stuff */
	//if(estado==0){
	//estado=1;
	
	//}else{
	//estado=0; 
	//}
	//digitalWrite (21, estado) ; 
		 
  //digitalWrite(21,HIGH);
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(PV_vsi_sf_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */
  
    //------Entradas-------
   digitalWrite(0,LOW);
  
  if (MCP3204_convert(fileDescriptor,singleEnded,CH1,&ad_MCP3204,error))
	{
		printf("Error during conversion1.\n");
		printf("%s\n",error);
		exit(1);
	}
	
	
	var3=MCP3204_getValue(ad_MCP3204);
	
  
  var=1;
  
  double k=(2*170)/2248.0;
  double vx=-170-(502*2*170)/2248.0;
    
  ipv=1.5;//500;   //Proveniente de la fuente de generación PV
  vload3=var3*k+vx; //Proveniente de la carga
  //vload=vload/10.0;
  
  set_Idc_PV(ipv);
  set_Vload3(vload3);

  /* Step the model for base rate */
  PV_vsi_sf_step();

  /* Get model outputs here */
  
//-------Salidas------
  i3=get_I_pv();
  soc=get_SOC();
  printf("La corriente del inversor 3 PV es: %3.2f \n",i3);
  printf("El estado de la bateria es: %3.2f \n",soc);
  printf ("La tensión en la carga es :%3.2f \n",vload3); 
  
  i3a=i3*10;
  
  memset(buffer3,0,sizeof(buffer3));
   //sprintf(buffer,"p%07dq%07dv%07ds%07d\n",Pma,Qma,Vloada,soca);
   sprintf(buffer3,"v%07d\n",i3a);
   //while(pinr==0){
	   serialPuts(fd3,buffer3);
	   serialFlush(fd3);
	   //pinr=digitalRead(2);
	   //printf("El dato pin es: %d \n",pinr);
   //}
   serialFlush(fd3);
   tcflush(fd3, TCIOFLUSH);
   pinr=0;
   
   var=0;
   
   //-----------Grafica---------------------
   //in+=0.0001;
   //fprintf(temp, "%3.2f %3.2f %3.2f %3.2f %3.2f %3.2f \n",i1,i2,i3,Vload,Pm,Qm);
   fprintf(temp3, "%3.2f %3.2f \n",i3,vload3);
  //}

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
  t.tv_nsec+=interval;
  tsnorm(&t);
  }
  PV_vsi_sf_terminate();
}


/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
	
  /* Unused arguments */
  (void)(argc);
  (void)(argv);
  pthread_t tid1, tid2, tid3;
  
  #if defined(_POSIX_THREAD_PRIO_INHERIT) && _POSIX_THREAD_PRIO_INHERIT != -1 && defined(USE_PRI_INHERIT)
	  printf("Using priority inheritance\n");
	  //~ if (pthread_mutexattr_setprotocol(&mutex_attr, PTHREAD_PRIO_INHERIT))
	  //~ {perror("mutex init"); exit(1);}
  #else
	printf("Not Using priority inheritance\n");
  #endif
  if (MCP3204_init(&fileDescriptor,"/dev/spidev1.2",&ad_MCP3204,mode_SPI_00,4.08,error))
    {
		printf("Cannot initialize the MCP3204 ADC.\n");
		printf("%s\n",error);
		exit(1); 
    }
    
  
  pthread_create(&tid1, NULL, rt_OneStep_Diesel, NULL);
  //pthread_create(&tid2, NULL, rt_OneStep_Bio, NULL);
  pthread_create(&tid3, NULL, rt_OneStep_PV, NULL);
  
  pthread_join(tid1, NULL);
  //pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
    
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
