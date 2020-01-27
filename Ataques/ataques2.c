//gcc ataques.c 
/*
    Syn Flood DOS with LINUX sockets
*/
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>   
        
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

int main(int argc, const char *argv[])
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
    
    
    
    //Para RT
    struct timespec t;
    struct sched_param param;
    /* default interval = 50000ns = 50us
     * cycle duration = 100us
     */
     
     //=============== Pipes Envio ========================
    memset(bufferPipe,0,sizeof(bufferPipe));
    sprintf(bufferPipe,"%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",i1,duty_cycle,Pm1,Qm1,potencia);
    write(our_output_fifo_filestream, (void*)bufferPipe, strlen(bufferPipe));
    //======================================================
    
    
    
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
    
    
    
    /* Unused arguments */
    (void)(argc);
    (void)(argv);
    
   
    /* Simulating the model step behavior (in non real-time) to
     *  simulate model behavior at stop time.
     */
    while (1) {
        
        /* wait untill next shot */
        //clock_nanosleep(0, TIMER_ABSTIME, &t, NULL);
        /* do the stuff */
        //=============== Pipes Envio ========================
        memset(bufferPipe,0,sizeof(bufferPipe));
        sprintf(bufferPipe,"%3.2f\n",123456789535353543.3);
        write(our_output_fifo_filestream, (void*)bufferPipe, strlen(bufferPipe));
        //======================================================
    }
    
    /* Disable rt_OneStep() here */
    
        
    //----- CLOSE THE FIFO -----
    
    (void)close(our_output_fifo_filestream);
    
    return 0;
}
