//compile using "gcc ert_main_New_Serial.c carga_new.c rt_nonfinite.c rtGetInf.c rtGetNaN.c libmcp3204.c -lm -lwiringPi -lrt -Wall"
/*               
 * File: ert_main.c
 *
 * Code generated for Simulink model 'carga_new'.
 *
 * Model version                  : 1.18
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Oct  4 11:56:21 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "carga_new.h"                 /* Model's header file */
#include "rtwtypes.h"
#include <wiringSerial.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>
//#include <ncurses.h>
//#include "libmcp3204.h"

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

#define MSGISIZE 26

//Ataques
#define BUFFER_SIZE 1024
const char *DoS = "ataqueDoS";
FILE *input_DoS;
char buffera[BUFFER_SIZE];
char *rDoS;

//------Entradas-------
double i1=0.0;
double i2=0.0;
double i3=0.0;
//MCP3204 ad_MCP3204;
int fileDescriptor;
char error[55];

//------Salidas--------
double Pm=0.0;
double Qm=0.0;
double Vload=0.0;
double min=5000;
double max=0.0;
double potencia=0.0;
double tiempo=0.0;


//Comunicacion
#include <stdbool.h> 

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
int Vloada=0;
int Pma=0;
int Qma=0;
char buffer[8];

bool stringComplete = false;  // whether the string is complete
bool conti = true;
char inputCharArray[125];
char delim[] = ",";
char *ptr;
int j = 0;
char inChar;
char *Bio_CA;
char *Dies_CA;
char *EnAlt_CA;
int Bio = 0,Dies = 0,EnAlt = 0;

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


int i;
int k;

// 39 datos
// Dt = 427us (idealmente) para 60Hz
int senw[] = {2048,	2377,	2697,	3000,	3278,
3525,	3733,	3898,	4015,	4081,
4094,	4055,	3963,	3822,	3634,
3406,	3143,	2851,	2538,	2213,
1883,	1558,	1245,	953,	690,
462,	274,	133,	41,	2,
15, 81,	198,	363,	571,
818, 1096,	1399,	1719};



//--------------Para RT-----------------
#include <time.h>
#include <sched.h>
//#include <wiringPi.h>

#define NSEC_PER_SEC    1000000000

//--------------------------------------


//===================  Para Pipes =========================
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define OUR_INPUT_FIFO_NAME "/tmp/dataC"

int our_input_fifo_filestream = -1;
int result;
char bufferPipe[128];
//=========================================================

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

void rt_OneStep(void);
void rt_OneStep(void)
{
    static boolean_T OverrunFlag = false;
    
    /* Disable interrupts here */
    
    /* Check for overrun */
    if (OverrunFlag) {
        rtmSetErrorStatus(carga_new_M, "Overrun");
        return;
    }
    
    OverrunFlag = true;
    
    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */
    
    //------- entradas-------------
    digitalWrite(0,LOW);
    //tcflush(fd, TCIOFLUSH);
    
    var=0;
    
    var=1;
    
    // ============================= recibe Serial===========================
    
    stringComplete = false;
    conti = true;
    serialFlush(fd);
    
    memset(inputCharArray, 0, sizeof(inputCharArray));
    //if (serialDataAvail (fd))
    //{
		while (conti) {
			inChar = serialGetchar(fd);
			if (inChar == 's') {
				j = 0;
				while (!stringComplete) {
					while (serialDataAvail (fd) > 0  && conti) {
						inChar = serialGetchar(fd);
						if (inChar == 'e') {
							stringComplete = true;
							conti = false;
						} else {
							inputCharArray[j] = inChar;
							j++;
						}
					}
				}
			}
		
		}
		serialFlush(fd);
		ptr = strtok(inputCharArray, delim);
		Bio_CA = ptr;
		Bio = atoi(Bio_CA);
		//vload = atoi(inputCharArray);
		ptr = strtok(NULL, delim);
		Dies_CA = ptr;
		Dies = atoi(Dies_CA);
		ptr = strtok(NULL, delim);
		EnAlt_CA = ptr;
		EnAlt = atoi(EnAlt_CA);
	//}
    
    
    //=======================================================================
    
    i1=Bio/10.0;
    i2=Dies/10.0;
    i3=EnAlt/10.0;
    
    tiempo=tiempo+0.0001;
    if (tiempo==0.0168) tiempo=0.0;
    //i3=i3/10.0;
    //Variables prubea generadores
    //i1=(16.67*2)*var1/4095.0-16.67;
    
    //i1=(16.67*2)*var1/255.0-16.67;
    //i2=i1;
    //i3=i1;
    //printf("Valor adc 1: %d \n", var1);
    //printf("Valor adc 2: %d \n", var2);
    
    
    
    //if (min>var1) min=var1;
    //if (max<var1) max=var1;
    
//     printf("Valor minimo: %3.2f \n", min);
//     printf("Valor maximo: %3.2f \n", max);
    
    
    //1000*sin(2*3.14*60*tiempo)
    
    set_i1(i1);
    set_i2(i2);
    set_i3(120*sin(2*3.14*60*tiempo));
    
    //set_i1((senw[i]-2048)*0.0391);
    //set_i2((senw[i]-2048)*0.0391);
    //set_i3((senw[i]-2048)*0.0391);
    
    printf ("i1: %f i2: %f i3: %f\n",i1,i2,i3);
    
    /* Step the model for base rate */
    carga_new_step();
    
    /* Get model outputs here */
    
    //----- salidas-------
    Pm=get_Pm();
    Qm=get_Qm();
    Vload=get_Vload();
    potencia=get_Potencia();
    
    printf("La potencia P medida es: %3.2f \n",Pm);
    printf("La potencia Q medida es: %3.2f \n",Qm);
    printf("Voltaje : %3.2f \n",Vload);
    
    //-----------Ataque----------------
    fgets(buffera, BUFFER_SIZE, input_DoS);
    //printf("El valor del ataque String es: %s\n",buffera);
    
    int ai=atoi(buffera);
    if (ai ==1) {
        Vload=0.0;
        printf("El valor del ataque es: %d\n",ai);
    }
    printf("La valor de tensión modificada es: %3.2f \n",Vload);
    
//     if (min>Vload) min=Vload;
//     if (max<Vload) max=Vload;
    
    //=============== Pipes Envio ========================
    memset(bufferPipe,0,sizeof(bufferPipe));
    sprintf(bufferPipe,"%3.2f\t%3.2f\t%3.2f\t%3.2f\n",Pm,Qm,Vload,potencia);
    write(our_input_fifo_filestream, (void*)bufferPipe, strlen(bufferPipe));
    //======================================================
    
    //----------Serial----------------------
    //-----------Escritura-envio---------------------

    Vloada=Vload*10;
    Pma=Pm*10;
    Qma=Qm*10;

    //Vloada = EnAlt+Dies+Bio;
    
    memset(buffer,0,sizeof(buffer));

    sprintf(buffer,"%d\n",Vloada);

    serialPuts(fd,buffer);
    
    serialFlush(fd);
    tcflush(fd, TCIOFLUSH);

    pinr=0;
    digitalWrite(1,LOW);
    var=0;
    
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
    
    //====================================================================
    //--------------------------------------
    //----- CREATE A FIFO / NAMED PIPE -----
    //--------------------------------------
    
    printf("Making FIFO...\n");
    result = mkfifo(OUR_INPUT_FIFO_NAME, 0777);		//(This will fail if the fifo already exists in the system from the app previously running, this is fine)
    if (result == 0)
    {
        //FIFO CREATED
        printf("New FIFO created: %s\n", OUR_INPUT_FIFO_NAME);
    }
    
    printf("Process %d opening FIFO %s\n", getpid(), OUR_INPUT_FIFO_NAME);
    our_input_fifo_filestream = open(OUR_INPUT_FIFO_NAME, (O_WRONLY | O_NONBLOCK));
    //Possible flags:
    //	O_RDONLY - Open for reading only.
    //	O_WRONLY - Open for writing only.
    //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
    //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
    //											immediately with a failure status if the output can't be written immediately.
    if (our_input_fifo_filestream != -1)
        printf("Opened FIFO: %i\n", our_input_fifo_filestream);
    //====================================================================
    
    
    input_DoS= fopen(DoS, "r");
    if (input_DoS == NULL){
        fprintf(stderr, "Unable to open file %s\n",DoS);
    }
    
    //Para RT
    struct timespec t;
    struct sched_param param;
    /* default interval = 50000ns = 50us
     * cycle duration = 100us
     */
    int interval=4*1000000;		//en ns   ->  20000=20us  20  100
    
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
    
    
    
    
    
    //------------GPIO---------------------
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(21, OUTPUT);
    //wiringPiISR(2, INT_EDGE_RISING, &lectura);
    pinMode(2, INPUT);
    digitalWrite(3,HIGH);
    digitalWrite(1,LOW);
    
    //if (MCP3204_init(&fileDescriptor,"/dev/spidev1.2",&ad_MCP3204,mode_SPI_00,4.08,error))
    //{
        //printf("Cannot initialize the MCP3204 ADC.\n");
        //printf("%s\n",error);
        //exit(1);
    //}
    
    /* Initialize model */
    carga_new_initialize();
    
    k=0;
    i=0;
    int estado=0;
    
    /* get current time */
    clock_gettime(0,&t);
    /* start after one second */
    t.tv_sec++;
    
    /* Simulating the model step behavior (in non real-time) to
     *  simulate model behavior at stop time.
     */
    while ((rtmGetErrorStatus(carga_new_M) == (NULL)) && !rtmGetStopRequested
            (carga_new_M)) {
        
        /* wait untill next shot */
        clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
        /* do the stuff */
        if(estado==0){
            estado=1;
            
        }else{
            estado=0;
        }
        digitalWrite (21, estado);
        i=i+1;
        if (i==35){
			i=0;
		}
        //digitalWrite (21, HIGH);
        rt_OneStep();
        //digitalWrite (21, LOW);
        t.tv_nsec+=interval;
        tsnorm(&t);
        
        
    }
    
    /* Disable rt_OneStep() here */
    
    /* Terminate model */
    carga_new_terminate();
    
    //----- CLOSE THE FIFO -----
    (void)close(our_input_fifo_filestream);
    
    return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
