##server.py

#Para OPC
from opcua import Server
from random import randint
import time

### Para Pipes
import os, sys
import fcntl
#pipe_name = '/tmp/my_fifo'
pipe_name = '/tmp/dataOutPV'
pipe_name2 = '/tmp/dataInPV'

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

IPV = Param.add_variable(addspace, "iPV",0)
SOC = Param.add_variable(addspace, "SOC",0)

PREF = Param.add_variable(addspace, "Pref",0) 
QREF = Param.add_variable(addspace, "Qref",0)


IPV.set_writable()
SOC.set_writable()
PREF.set_writable()
QREF.set_writable()

server.start()
print("Server started at ()".format(url))

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
    pref = 500
    qref = 3500
    while True:
        time.sleep(0.05)    
        try:
            #PipeString = os.read(PipeIn, bufferSize)
            #PipeString = PipeIn.readline()[:-1]
            PipeString = PipeIn.readline().split()

            pref1 = pref
            qref1 = qref
            pref = PREF.get_value()
            qref = QREF.get_value()
            if((pref1 != pref) or (qref1 != qref) ):
                print("Pref {}  Qref {}".format(pref,qref))
                string = str(pref)+'\t'+str(qref)+'\n'
                os.write(PipeIn2, str.encode(string))
            if not PipeString:
                #print ("Empty String!")
                continue;
            else:
                ipv = float(PipeString[0])
                soc = float(PipeString[1])
                #data4 = PipeString[3]
                #print('Received: "{0}\"'.format(PipeString))
                #print('Received: Ipv:{}\tsoc:{}'.format(ipv,soc))
                IPV.set_value(ipv)
                SOC.set_value(soc)
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


