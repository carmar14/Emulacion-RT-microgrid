/* compile using  "gcc -o b.out ert_main.c biomasa_data.c biomasa.c rt_nonfinite.c rtGetInf.c rtGetNaN.c libmcp3204.c -lm -lwiringPi -lrt -Wall"  */


/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'biomasa'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Oct  4 11:25:24 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "biomasa.h"                   /* Model's header file */
#include "rtwtypes.h"
#include <wiringSerial.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>
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
#define BUFFER_SIZE 1024
double valor_min=1000.0;
double valor_max=0.0;
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

//Ataques
const char *DoS = "ataqueDoS";
FILE *input_DoS;
char buffera[BUFFER_SIZE];
char *rDoS;
double num=0.0;

//------Salidas--------
double i1=0.0;
double duty_cycle=0.0;
double Pm1=0.0;
double Qm1=0.0;
double potencia=0.0;


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

//===================  Para Pipes =========================
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define OUR_INPUT_FIFO_NAME "/tmp/dataInBIO"
#define OUR_OUTPUT_FIFO_NAME "/tmp/dataOutBIO"

int our_output_fifo_filestream = -1;
int result, result2;
char bufferPipe[128];
FILE *fp;
char * pch;
int counter = 0;
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
void tarea(void);


void rt_OneStep(void)
{
    static boolean_T OverrunFlag = false;
    
    /* Disable interrupts here */
    
    /* Check for overrun */
    if (OverrunFlag) {
        rtmSetErrorStatus(biomasa_M, "Overrun");
        return;
    }
    
    OverrunFlag = true;
    
    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */
    
    /* Step the model for base rate */
    
    var=1;
    
    if (MCP3204_convert(fileDescriptor,singleEnded,CH0,&ad_MCP3204,error))
    {
        printf("Error during conversion1.\n");
        printf("%s\n",error);
        exit(1);
    }
    
    
    var1=MCP3204_getValue(ad_MCP3204);  //Vload
    
    
    
    
    double k=(2*170)/2248.0;
    double vx=-170-(502*2*170)/2248.0;
    k=500/873;
    vx=-787.51;
    
    
    //vdc=500;   //Proveniente de la fuente de generación
    //vload=170*sin(2*3.14*60*tiempo);//var1*k+vx; //Proveniente de la carga
    vload=var1*k+vx;
    tiempo=tiempo+0.0001;
    if (tiempo>0.0167) tiempo=0;
    
    //pref=var2*k2+vx2;//500.0;  //Proveniente del control terciario
    //qref=var3*k3+vx3;
    //pref=400;//500;   antes estaba en -400
    //qref=5000;//3500;//2430;//3403;
    
    //=============== Pipes Lectura ========================
    memset(bufferPipe,0,sizeof(bufferPipe));
    //printf("CB counter %d\n",counter);
    if(fgets(bufferPipe,sizeof(bufferPipe),fp) != NULL)
    {
        pref = strtof(bufferPipe,&pch);
        qref = strtof(pch,&pch);
        //printf("algo en buffer para Pref y Qref\n");
        counter++;
    }
    //else{printf("File empty");}
    //======================================================
    
    //set_Vdc_bio(vdc); // Ya no es necesario
    set_Vload(vload);
    set_Qref_bio(qref);
    set_Pref_bio(pref);
    
    
    biomasa_step();
    
    /* Get model outputs here */
    
    //------Salidas--------
    i1=get_I_bio();
    duty_cycle=get_duty_cycle();
    Pm1=get_Pm();
    Qm1=get_Qm();
    potencia=get_Potencia();
    
    //Verificando valores maximos y minimos
    if (i1 > valor_max){
         valor_max=i1;
    }
    if (i1 < valor_min){
        valor_min=i1;    
    }
    
    printf("El vload es : %3.2f \n",vload);
    printf("La potencia Pref es: %3.2f \n",pref);
    printf("La potencia Qref es: %3.2f \n", qref);
    printf("La potencia P medida es: %3.2f \n",Pm1);
    printf("La potencia Q medida es: %3.2f \n", Qm1);
    printf("La corriente del inversor 1 es: %3.2f \n",i1);
    printf("El duty de bio es: %3.2f \n",duty_cycle);
    printf("El valor minimo de corriente : %3.2f \n",valor_min);
    printf("El valor maximo de corriente : %3.2f \n",valor_max);
    
    
    //-----------Ataque----------------
    fgets(buffera, BUFFER_SIZE, input_DoS);
    //printf("El valor del ataque String es: %s\n",buffera);
    
    int ai=atoi(buffera);
    if (ai ==1) {
        i1=0.0;
        //printf("El valor del ataque es: %d\n",ai);
    }
    printf("La corriente del inversor modificada es: %3.2f \n",i1);
    
    //=============== Pipes Envio ========================
    memset(bufferPipe,0,sizeof(bufferPipe));
    sprintf(bufferPipe,"%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",i1,duty_cycle,Pm1,Qm1,potencia);
    //sprintf(bufferPipe,"%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",1.0,2.0,3.0,4.0,5.0);
    write(our_output_fifo_filestream, (void*)bufferPipe, strlen(bufferPipe));
    //======================================================
    
    //----------Serial----------------------
    //-----------Escritura-envio---------------------
    //Pma=Pm*10;
    //Qma=Qm*10;
    i1a=i1*10;
    
    memset(buffer,0,sizeof(buffer));
    //sprintf(buffer,"p%07dq%07dv%07ds%07d\n",Pma,Qma,Vloada,soca);
    sprintf(buffer,"v%07d\n",i1a);
    
    serialPuts(fd,buffer);
    serialFlush(fd);
    
    serialFlush(fd);
    tcflush(fd, TCIOFLUSH);
    pinr=0;
    
    var=0;
    
    //-----------Grafica---------------------
    //in+=0.0001;
    
    //fprintf(temp, "%3.2f %3.2f \n",vload,i1);
    
    //}
    
    /* Indicate task complete */
    OverrunFlag = false;
    
    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
}

//======================Tarea enfocada en el ataque DoS para saturacion de la red
void tarea(){
    
    
        num=num+0.000001;
        /* wait untill next shot */
        //clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
        /* do the stuff */
        //=============== Pipes Envio ========================
        memset(bufferPipe,0,sizeof(bufferPipe));
        sprintf(bufferPipe,"%3.2f\n",num);
        printf("El numero es %3.2f\n",num);
        write(our_output_fifo_filestream, (void*)bufferPipe, strlen(bufferPipe));
        
    
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
    
    printf("Making FIFO 1...\n");
    result = mkfifo(OUR_OUTPUT_FIFO_NAME, 0777);		//(This will fail if the fifo already exists in the system from the app previously running, this is fine)
    if (result == 0)
    {
        //FIFO CREATED
        printf("New FIFO 1 created: %s\n", OUR_OUTPUT_FIFO_NAME);
    }
    
    printf("Process %d opening FIFO 1 %s\n", getpid(), OUR_OUTPUT_FIFO_NAME);
    our_output_fifo_filestream = open(OUR_OUTPUT_FIFO_NAME, (O_WRONLY | O_NONBLOCK));
    //Possible flags:
    //	O_RDONLY - Open for reading only.
    //	O_WRONLY - Open for writing only.
    //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
    //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
    //											immediately with a failure status if the output can't be written immediately.
    if (our_output_fifo_filestream != -1)
        printf("Opened FIFO 1: %i\n", our_output_fifo_filestream);
    
    
    printf("Making FIFO 2...\n");
    result = mkfifo(OUR_INPUT_FIFO_NAME, 0777);		//(This will fail if the fifo already exists in the system from the app previously running, this is fine)
    if (result == 0)
    {
        //FIFO CREATED
        printf("New FIFO 2 created: %s\n", OUR_INPUT_FIFO_NAME);
    }
    
    printf("Process %d opening FIFO %s\n", getpid(), OUR_INPUT_FIFO_NAME);
    
    if((fp = fopen(OUR_INPUT_FIFO_NAME, "r+")) == NULL){
        printf("Something went wrong ");
        return EXIT_FAILURE;
    }
    int fdO = fileno(fp);
    int flags = fcntl(fdO, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fdO, F_SETFL, flags);
    printf("FIFO 2 opened...");
    
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
    
    printf("Iniciando \n");
    
    int interval=4*1000000;		// 4 en ns   ->  20000=20us   100
    
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
    
    /* Unused arguments */
    (void)(argc);
    (void)(argv);
    
    /* Initialize model */
    biomasa_initialize();
    
    int estado=0;
    /* Simulating the model step behavior (in non real-time) to
     *  simulate model behavior at stop time.
     */
    sleep(5);
    /* get current time */
    clock_gettime(0,&t);
    /* start after one second */
    t.tv_sec++;
    
    /* Simulating the model step behavior (in non real-time) to
     *  simulate model behavior at stop time.
     */
    while ((rtmGetErrorStatus(biomasa_M) == (NULL)) && !rtmGetStopRequested
            (biomasa_M)) {
        
        /* wait untill next shot */
        //clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
        /* do the stuff */
        if(estado==0){
            estado=1;
            
        }else{
            estado=0;
        }
        digitalWrite (21, estado) ;
        
        rt_OneStep();
        //tarea();
        
        t.tv_nsec+=interval;
        tsnorm(&t);
    }
    
    /* Disable rt_OneStep() here */
    
    /* Terminate model */
    biomasa_terminate();
    
    //----- CLOSE THE FIFO -----
    fclose(fp); //input fifo
    (void)close(our_output_fifo_filestream);
    
    return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
