##server.py

#Para OPC
from opcua import Server
from random import randint
import time

### Para Pipes
import os, sys
import fcntl
#pipe_name = '/tmp/my_fifo'
pipe_name = '/tmp/dataC'
pipe_name2 = '/tmp/dataC_In'

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

PM = Param.add_variable(addspace, "Pm",0)
QM = Param.add_variable(addspace, "Qm",0)
VLOAD = Param.add_variable(addspace, "Vload",0)
LOAD_REF = Param.add_variable(addspace, "Load_Ref",0)

PM.set_writable()
QM.set_writable()
VLOAD.set_writable()
LOAD_REF.set_writable()

server.start()
print("Server started at ()".format(url))

#=================================================

try:
    #PipeIn = os.open(pipe_name, os.O_RDONLY | os.O_NONBLOCK)
    print("Esperando abrir")
    PipeIn = open(pipe_name, "r")
    print("Pipe 1 running...")
    fd = PipeIn.fileno()
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    PipeIn2 = os.open(pipe_name2, os.O_WRONLY)
    print("Pipe 2 running...")
    print("Program running...")
    Lref = 0
    while True:
        time.sleep(0.05)    
        try:
            #PipeString = os.read(PipeIn, bufferSize)
            #PipeString = PipeIn.readline()[:-1]
            PipeString = PipeIn.readline().split()
            
            Lref1 = Lref
            Lref = LOAD_REF.get_value()
            
            if Lref1 != Lref :
                print("Load_Ref {}".format(Lref))
                string = str(Lref)+'\n'
                os.write(PipeIn2, str.encode(string))
            if not PipeString:
                #print ("Empty String!")
                continue;
            else:
                Pm = float(PipeString[0])
                Qm = float(PipeString[1])
                Vload = float(PipeString[2])
                #data4 = PipeString[3]
                #print('Received: "{0}\"'.format(PipeString))
                #print('Received: Idie:{}\tDuty Cycle:{}\tCaudal:{}'.format(Idie,Duty_cycle,Caudal))
                PM.set_value(Pm)
                QM.set_value(Qm)
                VLOAD.set_value(Vload)
        except OSError as err:
            if err.errno == 11:
                print("Nothing there")
                continue;
            else:
                raise err; 
except: 
    print("Error Closing Pipe")
    os.close(pipe_name)



