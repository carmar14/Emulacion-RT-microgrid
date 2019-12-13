// compile with "gcc ert_main.c carga_reno.c carga_reno_data.c rt_nonfinite.c rtGetInf.c rtGetNaN.c -lm -lwiringPi -lrt -Wall -lpthread


/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'carga_reno'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Dec 13 10:02:20 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "carga_reno.h"                /* Model's header file */
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



//Emulacion de panel
#define BUFFER_SIZE 1024
double Vg,Vc,n,Ns,T1,Voc_T1,Isc_T1,Isc_T2,T2,Voc_T2,Ics_T2,TaK,K0,IL_T1,IL,I0,I0_T1,Xv,dVdI_Voc,k,q,Rs,A,Vt_Ta,Ia;
double Suns,TaC,Va,Temp,Volt,Irra;

//Datos del txt
const char *delimiter_characters = "\t";
const char *filename = "perfiles_meteo_consum1/myData7_5min.txt";//"perfiles_meteo_consum/myData7_5min.txt";
FILE *input_file; //= fopen(filename, "r");
char buffer[BUFFER_SIZE];
char *last_token;
char *year;
char *day;
char *times;
char *outhum;
char *windspd;
char *rain;
char *solarrad2;
char *tempout2;
char *consumptp;
char *consumptq;
int contador;
int contador2=0;



//Ataques
#define BUFFER_SIZE 1024
const char *DoS = "ataqueDoS";
FILE *input_DoS;
char buffera[BUFFER_SIZE];
char *rDoS;

//------Entradas-------
//Carga
double i1=0.0;
double i3=0.0;
//MCP3204 ad_MCP3204;

//Renovables
double ipv=0.0;
//double vload3=0.0;
double Prefd=0.0;
double Qrefd=0.0;
double solarrad;
double tempout;
//double potencia=0.0;
int fileDescriptor;
char error[55];

//------Salidas--------
//Carga
double Pm=0.0;
double Qm=0.0;
double Vload=0.0;
double min=5000;
double max=0.0;
double potencia=0.0;
double tiempo=0.0;

//Renovables
double i2=0.0;
double soc=0.0;
double Pm2=0.0;
double Qm2=0.0;
double duty_cyle=0.0;


//Comunicacion   ------------Falta cuadrar esta parte de la comunicacion con el arduino
#include <stdbool.h>
#define MSGISIZE 26
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
int fd3;
int Vloada=0;
int Pma=0;
int Qma=0;
int i3a=0;
char buffer3[8];
char buffer2[8];

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
//int k;

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

#define OUR_INPUT_FIFO_NAME "/tmp/dataInPV"
#define OUR_OUTPUT_FIFO_NAME "/tmp/dataOutPV"

int our_output_fifo_filestream = -1;
int our_input_fifo_filestream = -1;
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
void rt_OneStep(void)
{
    static boolean_T OverrunFlag = false;
    
    /* Disable interrupts here */
    
    /* Check for overrun */
    if (OverrunFlag) {
        rtmSetErrorStatus(carga_reno_M, "Overrun");
        return;
    }
    
    OverrunFlag = true;
    
    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */
    //printf("Pre-Serial\n");
    // ============================= recibe Serial===========================
    //================Falta cuadrar esto========================
    stringComplete = false;
    conti = true;
    //serialFlush(fd3);
    
    memset(inputCharArray, 0, sizeof(inputCharArray));
    //printf("Pre-Serial\n");
    //if (serialDataAvail (fd3))
    //{
    while (conti) {
        inChar = serialGetchar(fd3);
        //printf("char obtained: %c\n",inChar);
        if (inChar == 's') {
            j = 0;
            //printf("encuentra s\n");
            while (!stringComplete) {
                while (serialDataAvail (fd3) > 0  && conti) {
                    inChar = serialGetchar(fd3);
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
    serialFlush(fd3);
    ptr = strtok(inputCharArray, delim);
    Bio_CA = ptr;
    Bio = atoi(Bio_CA);
    //vload = atoi(inputCharArray);
    ptr = strtok(NULL, delim);
    Dies_CA = ptr;
    Dies = atoi(Dies_CA);
    //ptr = strtok(NULL, delim);
    //EnAlt_CA = ptr; // Esto ya no iria
    //EnAlt = atoi(EnAlt_CA); // Esto ya no iria
    //}
    
    
    //=======================================================================
    //printf("Post-Serial\n");
    
    //=======================================================================
    Prefd=500;//500;
    Qrefd=3500;//3500;//2430;//3403;
    //=============== Pipes Lectura ========================
    memset(bufferPipe,0,sizeof(bufferPipe));
    //printf("CB counter %d\n",counter);
    if(fgets(bufferPipe,sizeof(bufferPipe),fp) != NULL)
    {
        Prefd = strtof(bufferPipe,&pch);
        Qrefd = strtof(pch,&pch);
        solarrad = strtof(pch,&pch);
        tempout = strtof(pch,&pch);
        
        //printf("algo en buffer para Pref y Qref\n");
        counter++;
    }
    //else{printf("File empty");}
    //======================================================
    
    TaC= tempout;//atof(tempout); //Lectura desde el txt
    Va=0.5;
    Suns=solarrad/1000.0; //atof(solarrad)/1000.0; //Lectura desde el txt
    TaK = 273 + TaC;
    IL_T1 = Isc_T1 * Suns;
    IL = IL_T1 + K0*(TaK - T1);
    I0= I0_T1*pow((TaK/T1),(3/n))*exp(-q*Vg/(n*k)*((1/TaK)-(1/T1)));
    Vt_Ta = A * k * TaK / q;
    Vc = Va/Ns;
    printf("Aqui estoy\n");
    
    for (int j=1;j<=5;j++){
        Ia=Ia- (IL - Ia - I0*( exp((Vc+Ia*Rs)/Vt_Ta) -1))/(-1 - (I0*( exp((Vc+Ia*Rs)/Vt_Ta) -1))*Rs/Vt_Ta);
    }
    
    ipv=1.5;//500;   //Proveniente de la fuente de generación PV
    //ipv=Ia;
    
    i1=Bio/10.0;
    i3=Dies/10.0;
    
    //i3=EnAlt/10.0;
    
    
    
    tiempo=tiempo+0.0001;
    if (tiempo==0.0168) tiempo=0.0;
    
    //Carga
    set_i1(i1);
    set_i3(i3);
    //Renovables
    set_Idc_PV(ipv);
    set_Pref(Prefd);
    set_Qref(Qrefd);
    
    /* Step the model for base rate */
    carga_reno_step();
    
    /* Get model outputs here */
    //----- salidas-------
    //Carga
    Pm=get_Pm();
    Qm=get_Qm();
    Vload=get_Vload();
    potencia=get_Potencia();
    
    //Renovables
    i2=get_I_pv();
    soc=get_SOC();
    Pm2=get_Pm2();
    Qm2=get_Qm2();
    duty_cyle=get_duty_cycle();
    
    
//     if (i3>max){
//         max=i3;
//     }
//
//     if (i3<min){
//         min=i3;
//     }
    
    //printf("La irradianza es: %3.2f \n",Suns);
    //printf("La temperatura es: %3.2f \n",TaC);
//     printf("La minima es: %3.2f \n",min);
//     printf("La maxima es: %3.2f \n",max);
    printf("La potencia activa referencia es: %3.2f \n",Prefd);
    printf("La potencia reactiva referencia es: %3.2f \n",Qrefd);
    printf("LA potencia P medida es:  %3.2f \n",Pm2);
    printf("LA potencia Q medida es:  %3.2f \n",Qm2);
    printf("La corriente del inversor 3 es: %3.2f \n",i3);
    printf("El duty cycle es:  %3.2f \n",duty_cyle);
    
    
    printf("La potencia P medida en la carga es: %3.2f \n",Pm);
    printf("La potencia Q medida en la carga es: %3.2f \n",Qm);
    printf("Voltaje : %3.2f \n",Vload);
    printf ("i1: %f i2: %f i3: %f\n",i1,i2,i3);
    
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
    
    //=============== Pipes Envio ======================== (Falta ajustar)
    memset(bufferPipe,0,sizeof(bufferPipe));
    sprintf(bufferPipe,"%3.2f\t%3.2f\t%3.2f\t%3.2f\n",Pm,Qm,Vload,potencia);
    write(our_input_fifo_filestream, (void*)bufferPipe, strlen(bufferPipe));
    //======================================================
    
    //----------Serial----------------------
    //-----------Escritura-envio---------------------
    
    Vloada=Vload*10.0;
    Pma=Pm*10;
    Qma=Qm*10;
    i3a=i3*10.0; 
    
    //Vloada = i2;
    
    //Vloada = EnAlt+Dies+Bio;
    
    memset(buffer2,0,sizeof(buffer2));
    
    sprintf(buffer2,"s%d,%d,e\n",Vloada,i3a);
    
    serialPuts(fd3,buffer2);
    
    serialFlush(fd3);
    tcflush(fd3, TCIOFLUSH);
    
    
    
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
    int fd = fileno(fp);
    int flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);
    printf("FIFO 2 opened...");
    
    //====================================================================
    
    
    //Para emulacion de arreglo de paneles
    Va=0;
    q=1.6*pow(10,-19);
    k=1.38*pow(10,-23);
    n=1.12;
    Vg=1.12;
    Ns=36;
    T1=273+25;
    Voc_T1=21.06/Ns;
    Isc_T1=3.3;//3.8;
    Voc_T2=19/Ns;//17.05/Ns;
    Isc_T2=3.4;//3.92;
    K0=(Isc_T2 - Isc_T1)/(T2 - T1);
    I0_T1=Isc_T1/(exp(q*Voc_T1/(n*k*T1))-1);
    Xv = I0_T1*q/(n*k*T1) * exp(q*Voc_T1/(n*k*T1));
    dVdI_Voc = - 1.15/Ns / 2;
    Rs = - dVdI_Voc - 1/Xv;
    A=1;
    printf("Numero: %3.2f \n",I0_T1);
    
    //Verificando txt de datos
    //FILE *input_file = fopen(filename, "r");
    input_file = fopen(filename, "r");
    if (input_file == NULL){
        fprintf(stderr, "Unable to open file %s\n",filename);
    }
    fgets(buffer, BUFFER_SIZE, input_file);	//First line for the labels
    
    printf("Openeing ataque DoS\n");
    input_DoS= fopen(DoS, "r");
    if (input_DoS == NULL){
        fprintf(stderr, "Unable to open file %s\n",DoS);
    }
    
    //Para RT
    struct timespec t;
    
    /* default interval = 50000ns = 50us
     * cycle duration = 100us
     */
    int interval=4*1000000;		//en ns   ->  20000=20us 100
    
    
    //Grafica
    
    printf("Openeing data temp\n");
    temp = fopen("data.temp", "w");
    
    gnuplotPipe = popen ("gnuplot -persistent", "w");
    
    fprintf(gnuplotPipe,"set grid \n");
    
    //Serial
    printf("Openeing serial port\n");
    fd3=serialOpen ("/dev/ttyACM0", 115200);
    serialClose(fd3);
    fd3=serialOpen ("/dev/ttyACM0", 115200);
    
    serialFlush(fd3);
    tcflush(fd3, TCIOFLUSH);
    
    sleep(1);
    printf("Setting pin mode\n");
    //------------GPIO---------------------
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(21, OUTPUT);
    //wiringPiISR(2, INT_EDGE_RISING, &lectura);
    pinMode(2, INPUT);
    digitalWrite(3,HIGH);
    digitalWrite(1,LOW);
    
    int estado=0;
    
    //if (MCP3204_init(&fileDescriptor,"/dev/spidev1.2",&ad_MCP3204,mode_SPI_00,4.08,error))
    //{
    //printf("Cannot initialize the MCP3204 ADC.\n");
    //printf("%s\n",error);
    //exit(1);
    //}
    
    /* Unused arguments */
    (void)(argc);
    (void)(argv);
    
    /* Initialize model */
    printf("Initializing model\n");
    carga_reno_initialize();
    printf("Starting\n");
    /* get current time */
    clock_gettime(0,&t);
    /* start after one second */
    t.tv_sec++;
    
    /* Simulating the model step behavior (in non real-time) to
     *  simulate model behavior at stop time.
     */
    
    while ((rtmGetErrorStatus(carga_reno_M) == (NULL)) && !rtmGetStopRequested
            (carga_reno_M)) {
		
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
    carga_reno_terminate();
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
