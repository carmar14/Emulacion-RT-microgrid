##server.py

#Para OPC
from opcua import Server
from random import randint
import time

### Para Pipes
import os, sys
import fcntl
#pipe_name = '/tmp/my_fifo'
pipe_name = '/tmp/dataD'

#________Creacion Pipe__________
if not os.path.exists(pipe_name):
    print("File name not present... creating...\n")
    os.mkfifo(pipe_name)
    print("Pipe created\n")

else:
    print("File name already present\n")
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

#=================================================

try:
    #PipeIn = os.open(pipe_name, os.O_RDONLY | os.O_NONBLOCK)
    PipeIn = open(pipe_name, "r")
    print("Pipe and OPC running...")
    fd = PipeIn.fileno()
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    while True:
        #time.sleep(1)    
        try:
            #PipeString = os.read(PipeIn, bufferSize)
            #PipeString = PipeIn.readline()[:-1]
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
                #VDC.set_value(Vdc)
        except OSError as err:
            if err.errno == 11:
                print("Nothing there")
                continue;
            else:
                raise err; 
except: 
    print("Error Closing Pipe")
    os.close(pipe_name)



