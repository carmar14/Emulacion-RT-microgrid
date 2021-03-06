##server.py

#Para OPC
from opcua import Server
from random import randint
import time

### Para Pipes
import os, sys
import fcntl
#pipe_name = '/tmp/my_fifo'
pipe_name = '/tmp/dataOutBIO'
pipe_name2 = '/tmp/dataInBIO'
pipe_name3 = '/tmp/dataOutBIO1'
pipe_name4 = '/tmp/dataInBIO1'

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

if not os.path.exists(pipe_name3):
    print("File name 3 not present... creating...\n")
    os.mkfifo(pipe_name3)
    print("Pipe 3 created\n")

else:
    print("File name 3 already present\n")

if not os.path.exists(pipe_name4):
    print("File name 4 not present... creating...\n")
    os.mkfifo(pipe_name4)
    print("Pipe 4 created\n")

else:
    print("File name 4 already present\n")

#_______________________________


#============= Para OPC ==========================
server = Server()

url = "opc.tcp://0.0.0.0:4840"
server.set_endpoint(url)

name = "OPCUA_SIMULATION_SERVER"
addspace = server.register_namespace(name)

node = server.get_objects_node()

Param = node.add_object(addspace, "Parameters")

IBIO = Param.add_variable(addspace, "iBio",0)
#SOC = Param.add_variable(addspace, "SOC",0)

PREF = Param.add_variable(addspace, "Pref",0) 
QREF = Param.add_variable(addspace, "Qref",0)
PM = Param.add_variable(addspace, "Pm",0) 
QM = Param.add_variable(addspace, "Qm",0)
DC = Param.add_variable(addspace, "DuC",0)
POTENCIA = Param.add_variable(addspace, "Potencia",0)
IBIOa = Param.add_variable(addspace, "iBioa",0)
IBIOa1 = Param.add_variable(addspace, "iBioa1",0)
IBIOa2 = Param.add_variable(addspace, "iBioa2",0)
IBIOa3 = Param.add_variable(addspace, "iBioa3",0)
IBIOa4 = Param.add_variable(addspace, "iBioa4",0)
IBIOa5 = Param.add_variable(addspace, "iBioa5",0)
IBIOa6 = Param.add_variable(addspace, "iBioa6",0)


IBIO.set_writable()
#SOC.set_writable()
PREF.set_writable()
QREF.set_writable()
PM.set_writable()
QM.set_writable()
DC.set_writable()
POTENCIA.set_writable()
IBIOa.set_writable()
IBIOa1.set_writable()
IBIOa2.set_writable()
IBIOa3.set_writable()
IBIOa4.set_writable()
IBIOa5.set_writable()
IBIOa6.set_writable()

server.start()
print("Server started at ()".format(url))

#=================================================

try:
    #PipeIn = os.open(pipe_name, os.O_RDONLY | os.O_NONBLOCK)
    
    print("Esperando abrir")
    PipeIn = open(pipe_name, 'r')
    print("Pipe 1 running...")
    fd = PipeIn.fileno()
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)
    flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    PipeIn2 = os.open(pipe_name2, os.O_WRONLY)
    print("Pipe 2 running...")
    print("Program running...")
    
    print("Esperando abrir")
    PipeIn3 = open(pipe_name3, 'r')
    print("Pipe 3 running...")
    fd2 = PipeIn3.fileno()
    flag2 = fcntl.fcntl(fd2, fcntl.F_GETFL)
    fcntl.fcntl(fd2, fcntl.F_SETFL, flag2 | os.O_NONBLOCK)
    flag2 = fcntl.fcntl(fd2, fcntl.F_GETFL)
    PipeIn4 = os.open(pipe_name4, os.O_WRONLY)
    print("Pipe 4 running...")
    print("Program running...")
    
    pref = 500
    qref = 3500
    while True:
        time.sleep(0.05)    
        try:
            #PipeString = os.read(PipeIn, bufferSize)
            #PipeString = PipeIn.readline()[:-1]
            PipeString = PipeIn.readline().split()
            PipeString2 = PipeIn3.readline().split()

            pref1 = pref
            qref1 = qref
            pref = PREF.get_value()
            qref = QREF.get_value()
            if((pref1 != pref) or (qref1 != qref) ):
                print("Pref {}  Qref {}".format(pref,qref))
                string = str(pref)+'\t'+str(qref)+'\n'
                os.write(PipeIn2,str.encode(string))
            if not PipeString or not PipeString2:
                #print ("Empty String!")
                continue;
            else:
                iBio = float(PipeString[0])
                print("Corriente {} ".format(iBio))
                dc = float(PipeString[1])
                print("ciclo util {} ".format(dc))
                pm = float(PipeString[2])
                print("pm {} ".format(pm))
                qm = float(PipeString[3])
                print("qm {} ".format(qm))
                potencia=float(PipeString[4])
                print("potencia {} ".format(potencia))
                iBioa = float(PipeString2[0])
                iBioa1 = float(PipeString2[1])
                iBioa2 = float(PipeString2[2])
                iBioa3 = float(PipeString2[3])
                iBioa4 = float(PipeString2[4])
                iBioa5 = float(PipeString2[5])
                iBioa6 = float(PipeString2[6])
                
                #iBioa = float(34)
                print(iBioa)
                
                
                #soc = float(PipeString[1])
                #data4 = PipeString[3]
                #print('Received: "{0}\"'.format(PipeString))
                #print('Received: IBio:{}\tpm:{}\tqm:{}'.format(iBio,pm,qm))
                IBIO.set_value(iBio)
                PM.set_value(pm)
                QM.set_value(qm)
                DC.set_value(dc)
                POTENCIA.set_value(potencia)
                IBIOa.set_value(iBioa)
                IBIOa1.set_value(iBioa1)
                IBIOa2.set_value(iBioa2)
                IBIOa3.set_value(iBioa3)
                IBIOa4.set_value(iBioa4)
                IBIOa5.set_value(iBioa5)
                IBIOa6.set_value(iBioa6) 
                    
        except OSError as err:
            if err.errno == 11:
                print("Nothing there")
                continue;
            else:
                raise err; 
except OSError as err:
    raise err;
    print("Error! Closing Pipe")
    ##os.close(pipe_name)





