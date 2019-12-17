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

PM = Param.add_variable(addspace, "Pm",0)
QM = Param.add_variable(addspace, "Qm",0)
VLOAD = Param.add_variable(addspace, "Vload",0)

LREF = Param.add_variable(addspace, "Lref",0)
KB = Param.add_variable(addspace, "Kb",0)
KD = Param.add_variable(addspace, "Kd",0)

SOC = Param.add_variable(addspace, "SOC",0)
IPV = Param.add_variable(addspace, "iPV",0)
IRR = Param.add_variable(addspace, "Irr",0) 
TEMP= Param.add_variable(addspace, "Temp",0)

DC = Param.add_variable(addspace, "DuC",0)
PREF = Param.add_variable(addspace, "Pref",0) 
QREF = Param.add_variable(addspace, "Qref",0)
PM2 = Param.add_variable(addspace, "Pm",0) 
QM2 = Param.add_variable(addspace, "Qm",0)


PM.set_writable()
QM.set_writable()
VLOAD.set_writable()

LREF.set_writable()
KB.set_writable()
KD.set_writable()

SOC.set_writable()
IPV.set_writable()
IRR.set_writable()
TEMP.set_writable()

DC.set_writable()
PREF.set_writable()
QREF.set_writable()
PM2.set_writable()
QM2.set_writable()

KB.set_value(1)
IRR.set_value(1000)
TEMP.set_value(25)

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
    irr=1000
    temp=25
    
    while True:
        time.sleep(0.05)    
        try:
            #PipeString = os.read(PipeIn, bufferSize)
            #PipeString = PipeIn.readline()[:-1]
            PipeString = PipeIn.readline().split()

            pref1 = pref
            qref1 = qref
            irr1=irr
            temp1=temp
            pref = PREF.get_value()
            qref = QREF.get_value()
            irr = IRR.get_value()
            temp = TEMP.get_value()
            
            if((pref1 != pref) or (qref1 != qref) or (temp1 != temp) or (irr1 !=irr)):
                print(PipeString)
                print("Pref {}  Qref {} Irr {} Temp {}".format(pref,qref,irr,temp))
                string = str(pref)+'\t'+str(qref)+'\t'+str(irr)+'\t'+str(temp)+'\n'
                os.write(PipeIn2, str.encode(string))
            if not PipeString:
                #print ("Empty String!")
                continue;
            else:
                Pm = float(PipeString[0])
                Qm = float(PipeString[1])
                Vload = float(PipeString[2])
                
                ipv = float(PipeString[3])
                soc = float(PipeString[4])
                pm2 = float(PipeString[5])
                qm2 = float(PipeString[6])
                dc = float(PipeString[7])
                #data4 = PipeString[3]
                #print('Received: "{0}\"'.format(PipeString))
                #print('Received: Ipv:{}\tsoc:{}'.format(ipv,soc))
                PM.set_value(Pm)
                QM.set_value(Qm)
                VLOAD.set_value(Vload)
                
                IPV.set_value(ipv)
                SOC.set_value(soc)
                PM2.set_value(pm2)
                QM2.set_value(qm2)
                DC.set_value(dc)
                
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



