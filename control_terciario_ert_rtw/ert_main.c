// compile with "gcc ert_main.c control_terciario.c libmcp3204.c -lm -lwiringPi -lrt -Wall"
/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'control_terciario'.
 *
 * Model version                  : 1.67
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Tue Dec 11 16:22:48 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "control_terciario.h"         /* Model's header file */
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

//Variables creadas por el programador
 //------Entradas-------
 double soc=0.0;
 double Pm=0.0;
 double Qm=0.0;
 double kbP=0.0;
 double kdP=0.0;
 double kbQ=0.0;
 double kdQ=0.0;
 double Pdmax=0.0;
 double Pbmax=0.0;
 double Qdmax=0.0;
 double Qbmax=0.0;
 
 MCP3204 ad_MCP3204;
 int fileDescriptor;
 char error[55];

 //------Salidas--------
 double Pb=0.0;
 double Qb=0.0;
 double Pd=0.0;
 double Qd=0.0;
 
 //-----------------------Comunicacion serial----------------------
 int Pba=0;
 int Qba=0;
 int Pda=0;
 int Qda=0;
 int fd;
 int fd1;
 char bufferAux;
 char buffer[30]; 
 char buffera[7];
 char bufferb[7];
 char bufferc[7];
 char buffer2[50];
 int var=0;
 //char dato[56];
 char dato[5];
 int datoi[5];
 char prueba[5]={'a','b','c','d','e'};
 char aux;
 double dato2;
 int aux2=0;
 int var1=0;
 int var2=0;
 int var3=0;
 char var1s[7];
 char var2s[7];
 char var3s[7];
 char read_buffer[25];   /* Buffer to store the data received              */
 int  bytes_read = 0;    /* Number of bytes read by the read() system call */
 int i = 0;
 
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
//------------------------------------------------------------------

void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(control_terciario_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */
  
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
	
	//Ajustar de acuerdo a simulacion
	double k1=8000/1657.0;
	double vx1=-(8000*550)/1657.0;
	double k2=25000/1657.0;
	double vx2=-25000*2207/1657.0;
  //-------entradas-------------
  Pm=var1*k1+vx1;
  Qm=var2*k2+vx2;
  soc=99.0;//var3;
  kbP=1.0;
  kdP=1.0;
  kbQ=1.0;
  kdQ=1.0;
  Pdmax=500.0;
  Pbmax=500.0;
  Qdmax=3500.0;
  Qbmax=3500.0;
  
   
  set_soc(soc);
  set_Pm(Pm);
  set_Qm(Qm);
  set_kbP(kbP);
  set_kbQ(kbQ);
  set_kdP(kdP);
  set_kdQ(kdQ);
  set_Pdmax(Pdmax);
  set_Pbmax(Pbmax);
  set_Qdmax(Qdmax);
  set_Qbmax(Qbmax);
  
  
  /* Step the model for base rate */
  control_terciario_step();
  

  /* Get model outputs here */
  
  //----- salidas-------
  Pb=get_Pb();
  Pd=get_Pd();
  Qb=get_Qb();
  Qd=get_Qd();
  
  printf ("Potencia Pm, Qm: %3.2f %3.2f \n",Pm,Qm);
  printf ("Pb: %f Pd: %f Qb: %f Qd: %f\n",Pb,Pd,Qb,Qd);
   
  //----------Serial----------------------
  //-----------Escritura-envio---------------------
  //Pma=Pm*10;
  //Qma=Qm*10;
  Pba=Pb*10; 
  Qba=Qb*10;
  Pda=Pd*10;
  Qda=Qd*10;
  
  memset(buffer,0,sizeof(buffer));
   //sprintf(buffer,"p%07dq%07dv%07ds%07d\n",Pma,Qma,Vloada,soca);
   sprintf(buffer,"v%07d%07d%07d%07de\n",Pba,Pda,Qba,Qda);
   //while(pinr==0){
	   serialPuts(fd,buffer);
	   serialPuts(fd1,buffer);
	   serialFlush(fd);
	   serialFlush(fd1);
	   //pinr=digitalRead(2);
	   //printf("Los datos son: %s \n",buffer);
   //}
   
   tcflush(fd, TCIOFLUSH);
   tcflush(fd1, TCIOFLUSH);
   
   
   
   
   //-----------Grafica---------------------
   //in+=0.0001;
   //fprintf(temp, "%3.2f %3.2f %3.2f %3.2f %3.2f %3.2f \n",i1,i2,i3,Vload,Pm,Qm);
   fprintf(temp, "%3.2f %3.2f %3.2f %3.2f \n",Pb,Pd,Qb,Qd);
   
  /* Indicate task complete */
  OverrunFlag = false;

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
	int interval=4*1000000;		//en ns   ->  20000=20us
  /* Unused arguments */
  (void)(argc);
  (void)(argv);
  
  //Grafica
  i=0;
  
  temp = fopen("data.temp", "w");
    
   gnuplotPipe = popen ("gnuplot -persistent", "w");
    
  fprintf(gnuplotPipe,"set grid \n");
  
  //Serial
  
  fd=serialOpen ("/dev/ttyACM0", 115200);
  serialClose(fd);
  fd=serialOpen ("/dev/ttyACM0", 115200);
  
  fd1=serialOpen ("/dev/ttyACM1", 115200);
  serialClose(fd1);
  fd1=serialOpen ("/dev/ttyACM1", 115200);
  
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
  
  int estado=0;
  
  if (MCP3204_init(&fileDescriptor,"/dev/spidev1.2",&ad_MCP3204,mode_SPI_00,4.08,error))
		{
			printf("Cannot initialize the MCP3204 ADC.\n");
			printf("%s\n",error); 
			exit(1);
		}


  /* Initialize model */
  control_terciario_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.0001 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */
   /* get current time */
  clock_gettime(0,&t);
  /* start after one second */
  t.tv_sec++;
  
  
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(control_terciario_M) == (NULL)) {
    /*  Perform other application tasks here */
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
	    
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  control_terciario_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
