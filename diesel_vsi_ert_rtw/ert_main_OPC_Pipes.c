// compile with: "gcc ert_main_OPC_Pipes.c diesel_vsi.c rt_nonfinite.c rtGetInf.c rtGetNaN.c libmcp3204.c  -lm -lwiringPi -lrt -Wall"
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
#include "diesel_vsi.h"             /* Model's header file */
#include "rtwtypes.h"
#include <wiringSerial.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>
#include <stdint.h>
//#include <ncurses.h>
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
//Variables creadas por el programador
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
double caudal=0.0;
double vdc=0.0;
double min=5000;
double max=0.0;
double duty_cycle=0.0;

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
int fd2;
int i2a=0;
int caudala=0;
char buffer[8];
char buffer2[8];
double tiempo=0.0;

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



//===================  Para Pipes =========================
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define OUR_INPUT_FIFO_NAME "/tmp/dataD"

int our_input_fifo_filestream = -1;
int result;
char bufferPipe[128];
//=========================================================

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
        rtmSetErrorStatus(diesel_vsi_M, "Overrun");
        return;
    }
    
    OverrunFlag = true;
    
    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */
    //-------entradas-------------
    //digitalWrite(0,LOW);
    /*tcflush(fd, TCIOFLUSH);
     * var=0;
     * //(read_buffer,0,sizeof(read_buffer));
     * //printf("Va leer 2\n");
     * memset(&bufferAux,0,sizeof(bufferAux));
     * //printf("Va leer\n");
     * //sprintf(read_buffer,"b%07dd%07de\n",Pma,Qma);
     * while(serialDataAvail(fd)==0){}
     *
     * memset(read_buffer,0,sizeof(read_buffer));
     * //printf("Captó dato serial\n");
     *
     * //Nuevooooooooo
     * while(read_buffer[0]!='f' && read_buffer[MSGISIZE-1]!='e'){
     * bytes_read=read(fd,&read_buffer,MSGISIZE);
     * serialFlush(fd);
     * tcflush(fd, TCIOFLUSH);
     * }
     *
     * //Nuevoooooo
     * digitalWrite(0,HIGH);
     * serialFlush(fd);
     * tcflush(fd, TCIOFLUSH);
     */
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
    
    //printf("Trama de arduino: %s\n",read_buffer);
    
    /*if (var==1){
     * int q=0;
     * //Acomodar en arreglo de caracteres los datos recibidos
     * for(q=0; q<7;q++){
     * var1s[q]=read_buffer[q+1]; //Primer dato
     * //var2s[q]=read_buffer[q+10]; //Segundo dato
     * //var3s[q]=read_buffer[q+18]; //Tercer dato
     * }
     * var1=atoi(var1s);//Primer dato en numero
     * //var2=atof(var2s)/10.0; //Segundo dato en numero
     * //var3=atof(var3s)/10.0; //Segundo dato en numero
     *
     * //var3=atof(var3s)/10.0; //Segundo dato en numero
     * //printf ("El numero1  es :%d \n",var1);
     * //printf ("El numero2  es :%3.2f \n",var2);
     * //printf ("El numero3  es :%3.2f \n",var3);
     */
    
    double k=(2*170)/2248.0;
    double vx=-170-(502*2*170)/2248.0;
    //double k=(2220+2150)/4095;
    //double vx=-2150;
    
    Pref_d=500;
    Qref_d=3500;
    Vload=var1*k+vx;
    //Vload=170*sin(2*3.14*60*tiempo);
    tiempo=tiempo+0.0001;
    if (tiempo>=0.017) tiempo =0;
    //Vload=Vload/10.0;
    par=0.1;//1.4;
    flujo=1000;
    
    //set_Pref_d(Pref_d);
    //set_Qref_d(Qref_d);
    set_Vload(Vload);
    set_par(par);
    set_flujo(flujo);
    
    /* Step the model for base rate */
    diesel_vsi_step();
    
    /* Get model outputs here */
    //-----salidas-------
    Idie=get_I_die();
    caudal=get_flujo();
    vdc=get_vdc();
    duty_cycle=get_duty();
    
    printf("La corriente del inversor 3 es: %3.2f \n",Idie);
    printf("La tension de la carga es : %3.2f \n",Vload);
    printf("El flujo es : %3.2f \n",caudal);
    printf("El nivel del bus dc es: %3.2f \n",vdc);
    printf("El dutyc es: %3.2f \n",duty_cycle);
    
    if (min>Idie) min=Idie;
    if (max<Idie) max=Idie;
    
    printf("Valor minimo: %3.2f \n", min);
    printf("Valor maximo: %3.2f \n", max);
    
    
    //=============== Pipes Envio ========================
    memset(bufferPipe,0,sizeof(bufferPipe));
    sprintf(bufferPipe,"%3.2f\t%3.2f\t%3.2f\t%3.2f\n",Idie,duty_cycle,caudal,vdc);
    write(our_input_fifo_filestream, (void*)bufferPipe, strlen(bufferPipe));
    //======================================================
    
    
    
    //-------------UDP-envio----------------------
    //sendm(Idie);
    //sendm(duty_cycle);
    
    //----------Serial----------------------
    //-----------Escritura-envio---------------------
    //Pma=Pm*10;
    //Qma=Qm*10;
    i2a=Idie*10;
    caudala=caudal*10;
    
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
    
    //Datos del caudal Bayona
    memset(buffer2,0,sizeof(buffer2));
    //sprintf(buffer,"p%07dq%07dv%07ds%07d\n",Pma,Qma,Vloada,soca);
    sprintf(buffer2,"v%07d\n",caudala);
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
    //fprintf(temp, "%3.2f %3.2f %3.2f %3.2f %3.2f %3.2f \n",i1,i2,i3,Vload,Pm,Qm);
    
    //fprintf(temp, "%3.2f %3.2f \n",Idie,Vload);
    
    
    //}
    
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
    
    //Para RT
    struct timespec t;
    struct sched_param param;
    /* default interval = 50000ns = 50us
     * cycle duration = 100us
     */
    int interval=4*1000000;		//en ns   ->  20000=20us     *4  100
    
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
    
    fd=serialOpen ("/dev/ttyACM0", 115200);  //0 Para la corriente del generador diesel
    serialClose(fd);
    fd=serialOpen ("/dev/ttyACM0", 115200);
    
    //fd2=serialOpen ("/dev/ttyACM1", 9600);
    //serialClose(fd2);
    //fd2=serialOpen ("/dev/ttyACM1", 9600);
    
    sleep(1);
    
    //Inicializar comunicacion UDP---------------------------------------------------------
    //setUDP();
    
    //------------GPIO---------------------
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
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
    
    delay(1500);
    /* Initialize model */
    diesel_vsi_initialize();
    
    int estado=0;
    
    /* get current time */
    clock_gettime(0,&t);
    /* start after one second */
    t.tv_sec++;
    
    
    /* Simulating the model step behavior (in non real-time) to
     *  simulate model behavior at stop time.
     */
    while ((rtmGetErrorStatus(diesel_vsi_M) == (NULL)) && !rtmGetStopRequested
            (diesel_vsi_M)) {
        /* wait untill next shot */
        clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
        /* do the stuff */
        if(estado==0){
            estado=1;
            
        }else{
            estado=0;
        }
        digitalWrite (0, estado) ;
        rt_OneStep();
        t.tv_nsec+=interval;
        tsnorm(&t);
    }
    
    /* Disable rt_OneStep() here */
    
    /* Terminate model */
    diesel_vsi_terminate();
    
    //----- CLOSE THE FIFO -----
	(void)close(our_input_fifo_filestream);
    
    return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */



//
// /*
//  * File: ert_main.c
//  *
//  * Code generated for Simulink model 'diesel_vsi'.
//  *
//  * Model version                  : 1.15
//  * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
//  * C/C++ source code generated on : Mon Jan 21 15:38:20 2019
//  *
//  * Target selection: ert.tlc
//  * Embedded hardware selection: Intel->x86-64 (Windows64)
//  * Code generation objectives: Unspecified
//  * Validation result: Not run
//  */
//
// #include <stddef.h>
// #include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
// #include "diesel_vsi.h"                /* Model's header file */
// #include "rtwtypes.h"
//
// /*
//  * Associating rt_OneStep with a real-time clock or interrupt service routine
//  * is what makes the generated code "real-time".  The function rt_OneStep is
//  * always associated with the base rate of the model.  Subrates are managed
//  * by the base rate from inside the generated code.  Enabling/disabling
//  * interrupts and floating point context switches are target specific.  This
//  * example code indicates where these should take place relative to executing
//  * the generated code step function.  Overrun behavior should be tailored to
//  * your application needs.  This example simply sets an error status in the
//  * real-time model and returns from rt_OneStep.
//  */
// void rt_OneStep(void);
// void rt_OneStep(void)
// {
//     static boolean_T OverrunFlag = false;
//
//     /* Disable interrupts here */
//
//     /* Check for overrun */
//     if (OverrunFlag) {
//         rtmSetErrorStatus(diesel_vsi_M, "Overrun");
//         return;
//     }
//
//     OverrunFlag = true;
//
//     /* Save FPU context here (if necessary) */
//     /* Re-enable timer or interrupt here */
//     /* Set model inputs here */
//
//     /* Step the model for base rate */
//     diesel_vsi_step();
//
//     /* Get model outputs here */
//
//     /* Indicate task complete */
//     OverrunFlag = false;
//
//     /* Disable interrupts here */
//     /* Restore FPU context here (if necessary) */
//     /* Enable interrupts here */
// }
//
// /*
//  * The example "main" function illustrates what is required by your
//  * application code to initialize, execute, and terminate the generated code.
//  * Attaching rt_OneStep to a real-time clock is target specific.  This example
//  * illustrates how you do this relative to initializing the model.
//  */
// int_T main(int_T argc, const char *argv[])
// {
//     /* Unused arguments */
//     (void)(argc);
//     (void)(argv);
//
//     /* Initialize model */
//     diesel_vsi_initialize();
//
//     /* Simulating the model step behavior (in non real-time) to
//      *  simulate model behavior at stop time.
//      */
//     while ((rtmGetErrorStatus(diesel_vsi_M) == (NULL)) && !rtmGetStopRequested
//             (diesel_vsi_M)) {
//         rt_OneStep();
//     }
//
//     /* Disable rt_OneStep() here */
//
//     /* Terminate model */
//     diesel_vsi_terminate();
//     return 0;
// }
//
// /*
//  * File trailer for generated code.
//  *
//  * [EOF]
//  */
