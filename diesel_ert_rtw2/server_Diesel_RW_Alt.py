##server.py

#Para OPC
from opcua import Server
from opcua import Client
from random import randint
import time

### Para Pipes
import os, sys
import fcntl
#pipe_name = '/tmp/my_fifo'
pipe_name = '/tmp/dataOutD'
pipe_name2 = '/tmp/dataInD'

#________Creacion Pipe__________
if not os.path.exists(pipe_name):
    print("File name 1 not present... creating...\n")
    os.mkfifo(pipe_name)
    print("Pipe 1 created\n")

else:
    print("File name 1 already present\n")

if not os.path.exists(pipe_name2):
    print("File name 2 not present... creating...\n")
    os.mkfifo(pipe_name2)
    print("Pipe 2 created\n")

else:
    print("File name 2 already present\n")
#_______________________________



#============= Para OPC ==========================
server = Server()

url = "opc.tcp://0.0.0.0:4840"
server.set_endpoint(url)

name = "OPCUA_SIMULATION_SERVER"
addspace = server.register_namespace(name)

node = server.get_objects_node()

Param = node.add_object(addspace, "Parameters")

IDIE = Param.add_variable(addspace, "iDies",0)
DUTY = Param.add_variable(addspace, "DiesDuty",0)
POTENCIA= Param.add_variable(addspace, "Potencia",0)

IDIE.set_writable()
DUTY.set_writable()
POTENCIA.set_writable()

server.start()
print("Server started at ()".format(url))

#===================================================


#============= OPC Client ==========================
conex = False
c_url = "opc.tcp://172.16.49.84:4840"   #IP and Port from server

client = Client(c_url)
while not conex:
    try:
        client.connect()
        conex=True
    except:
        #print("No client conection")
        continue
print("Client Connected")
#=================================================

try:
    #PipeIn = os.open(pipe_name, os.O_RDONLY | os.O_NONBLOCK)
    PipeIn = open(pipe_name, 'r')
    print("Pipe 1 running...")
    fd = PipeIn.fileno()
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    PipeIn2 = os.open(pipe_name2, os.O_WRONLY)
    print("Pipe 2 running...")
    print("Program running...")
    VLOAD = client.get_node("ns=2;i=4")
    vload = 0
    while True:
        #time.sleep(0.004)    
        try:
            #PipeString = os.read(PipeIn, bufferSize)
            #PipeString = PipeIn.readline()[:-1]
            PipeString = ""
            PipeString = PipeIn.readline().split()
            if not PipeString:
                #print ("Empty String!")
                continue;
            else:
                Idie = float(PipeString[0])
                Duty_cycle = float(PipeString[1])
                potencia = float(PipeString[2])
                #data4 = PipeString[3]
                #print('Received: "{0}\"'.format(PipeString))
                #print('Received: Idie:{}\tDuty Cycle:{}\tCaudal:{}'.format(Idie,Duty_cycle,Caudal))
                IDIE.set_value(Idie)
                DUTY.set_value(Duty_cycle)
                POTENCIA.set_value(potencia)
                
            vload = VLOAD.get_value()
            string = str(vload)+'\n'
            os.write(PipeIn2, str.encode(string))
            
        except OSError as err:
            if err.errno == 11:
                print("Nothing there")
                continue;
            else:
                raise err; 
except: 
    print("Error Closing Pipe")
    ##os.close(pipe_name)



