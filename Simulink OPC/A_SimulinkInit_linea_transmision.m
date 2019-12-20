% este script es ejecutado al momento de ejecutar el modelo de simulink de
% la microgrid de esta carpeta.
% En la seccion de configuracion de simulink, En la pestaña de callBacks se
% configuran los scripts que se desean ejectar al incio, durante o al
% final de la simulacion.
clear
close all
clc

K1d=1.15; K2d=1; K3d=1; Tao1d=0.5; Tao2d=0.125; Jd=0.3; Pd=0.1;

H_AM = tf([K1d*(K2d*K3d)],[Tao2d 1],'IODelay', Tao1d); % Dinámica Actuador - Motor
H_AM_d = c2d(H_AM,0.01,'tustin')

H_E = tf([Jd*Pd],[1 (Jd*Pd)]); % Dinámica Eje
H_E_d = c2d(H_E,0.01,'tustin')

%  Design MPC Controller

%   MPCOBJ = mpc(PLANT,TS,P,M) specifies the control horizon, M. M is
%   either an integer (<= P) or a vector of blocking factors such that
%   sum(M) <= P.
%   MODELS.Plant = plant model (LTI or IDMODEL)
%         .Disturbance = model describing the input disturbances.
%                           This model is assumed to be driven by unit
%                          variance white noise.
%            .Noise = model describing the plant output measurement noise.
%                           This model is assumed to be driven by unit
%                          variance white noise.
%            .Nominal = structure specifying the plant nominal conditions
%                             (e.g., at which the plant was linearized).

% Create the controller object with sampling period, prediction and control horizons:
load('mpc_linea_transmision.mat')
CSTR = ss1;%ss(Ab,Bb,Cb,Db);
CSTR.InputName = {'Pin_bio', 'Qin_bio','Pin_gen', 'Qin_gen'}; %u=[Pi_bio.Data Qi_bio.Data Pi_diesel.Data Qi_diesel.Data];
CSTR.OutputName = {'Pout_bio', 'Qout_bio','Pout_gen', 'Qout_gen'}; %y=[Po_bio.Data Qo_bio.Data Po_diesel.Data Qo_diesel.Data];
Ts = 1e-1;
p = 100;
m = 100;
mpcobj = mpc(CSTR, Ts, p, m);

% Specify actuator saturation limits as MV constraints.
% mpcobj.MV = struct('Min',{-200;-200},'Max',{200;200},'RateMin',{-100;-100});
% Simulate Using Simulink®

% To run this example, Simulink® is required.
% if ~mpcchecktoolboxinstalled('simulink')
%     disp('Simulink(R) is required to run this example.')
%     return
% end

% n11=tf1.Numerator{1,1};
% n12=tf1.Numerator{1,2};
% n21=tf1.Numerator{2,1};
% n22=tf1.Numerator{2,2};
% d11=tf1.Denominator{1,1};
% d12=tf1.Denominator{1,2};
% d21=tf1.Denominator{2,1};
% d22=tf1.Denominator{2,2};
% 
% N=[n11 n12; n21 n22];
% D=[d11 d12; d21 d22];
% [A1 B1 C1 D1]=tf2ss([n11; n12],[d11])
% [A2 B2 C2 D2]=tf2ss([n21; n22],[d11])
% [A3 B3 C3 D3]=tf2ss([n11; n12],[d12])
% [A4 B4 C4 D4]=tf2ss([n21; n22],[d12])
% [A5 B5 C5 D5]=tf2ss([n11; n12],[d21])
% [A6 B6 C6 D6]=tf2ss([n21; n22],[d21])
% [A7 B7 C7 D7]=tf2ss([n11; n12],[d22])
% [A8 B8 C8 D8]=tf2ss([n21; n22],[d22])


%Parametros 1:Biomasa 2:Diesel 3:VSI
% R1=0.1;
% R2=0.1;
% R3=1e-3;
% C1=22e-6;
% C2=22e-6;
% C3=610e-6;
% Cl=2000e-6;
% C=C1+C2+C3+Cl;
% L1=40e-3;
% L2=5e-3;
% L3=30e-3;
% L4=5.2;
% R4=10;
% R5=10;


%BIO
R1=0.1;
L1=40e-3;
C1=22e-6;
R4=0.005;%10;
L4=35e-6;%1e-3;

%REN
R2=0.2;
L2=30e-3;
C2=22e-6;
R5=0.0012;%40;  
L5=22e-6;%10e-3;

%DIESEL
R3=1e-3;
L3=5e-3;
C3=610e-6;
R6=0.001;
L6=10e-6;

%Carga
RL=10;
R=10;
L=5.2;
Cl=20000e-6;%20000e-6;

% Matrices desde el inversor hacia la carga sin el controlador
ssAl=[-R1/L1 zeros(1,6) -1/L1 zeros(1,3);
    0 -R2/L2 zeros(1,6) -1/L2 0 0;
    zeros(1,2) -R3/L3 zeros(1,6) -1/L3 0;
    zeros(1,3) -R4/L4 zeros(1,3) 1/L4 0 0 -1/L4;
    zeros(1,4) -R5/L5 zeros(1,3) 1/L5 0 -1/L5;
    zeros(1,5) -R6/L6 zeros(1,3) 1/L6 -1/L6;
    zeros(1,6) -R/L zeros(1,3) 1/L;
    1/C1 zeros(1,2) -1/C1 zeros(1,7);
    0 1/C2 0 0 -1/C2 zeros(1,6);
    0 0 1/C3 0 0 -1/C3 zeros(1,5);
    zeros(1,3) 1/Cl 1/Cl 1/Cl -1/Cl zeros(1,3) -1/(Cl*RL)]; 
ssBl=[1/L1 0 0;
   0 1/L2 0;
   0 0 1/L3;
   zeros(8,3)];
C11=[zeros(1,3) 1 zeros(1,7)]; %Salida del BIO
C22=[zeros(1,4) 1 zeros(1,6)]; %Salida del renovable
C33=[zeros(1,5) 1 zeros(1,5)]; %Salida del Diesel
C44=[zeros(1,10) 1];
ssCl=[C11; C22; C33;C44];
D=zeros(4,3);

%Tabla 1
cvsi=200/sqrt(2);
carga=cvsi*20;
q=0:0.001:carga*1.2;
soc=100-100*q/carga;

%Parámetros del sistema BIOMASA
factor_t=24*3600;
b=4.91;
Ks=21.5;
Ksc=3;
Kd=0.02;
Kdc=0.02;
K1=9.66;
K2=6.97;
K3=31.8;
K4=15.1;
Sbin=13.8;%13.8;  0.65
Svin=2.91;%2.91;    85
V=20;
wref=70000;%70000;
K=25;
K11=0.8;
K22=0.2;
T1s=0.4;
T2s=1;
T3s=15;
T4s=2.5;
T5s=3.3;
Tt=450;
Kv=1;
Tv=0.05;
C=1;
K33=0.23;
Kf=1;
Tr=950;%950; 100
Tf=0.04;
Tcr=0.01;
Ttd=0.04;
Tcd=0.2;
Kh=1.2;
Z=3;

X_acid=1.2;
S_b=4.51;
S_v=0.63;
X_meth=0.35;


%%=============Observadores para la deteccion y el aislamiento
%Matrices para el diseño del observador de Luenberger
% sys=ss(ssAl,ssBl,ssCl,[]);
sys=ss(ssAl,ssBl,ssCl,D);
tm=1e-5;%1e-4  del controlador pr 0.0001
sysd=c2d(sys,tm);
Ad=sysd.A;
Bd=sysd.B;
Cd=sysd.C;
Dd=sysd.D;
%con tm=1e-5;
po=1000*[-1.92*10 -1.92*10.1 -1.92*10.3 -1.92*10.2 -1.92*10.4 -1.92*10.5 -1.92*10.6 -1.92*10.7 -1.92*10.8 -1.92*10.9 -1.92*11];
% po=1000*[-71.36*10 -71.36*10.1 -71.36*10.3 -71.36*10.2 -71.36*10.4 -71.36*10.5 -71.36*10.6 -71.36*10.7 -71.36*10.8 -71.36*10.9 -71.36*11];
pod=exp(po*tm);
Ld=place(Ad',Cd',pod);

%UIO1 para el ataque del sensor 1 eliminamos esa fila de la matriz C

Fd1=[1e-4;1e-4;1.0e-4;1.0e-4;1;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
% Fd1=[1.0e-4;1;1;1;1];
% C1=Cd(2:end,:);
% C1=Cd(1,:);
C1o=Cd(2,:);
Fd2=[1.0e-4;1e-4;1e-4;1.0e-4;1.0e-4;1;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
% Fd2=[1; 1.0e-4;1;1;1];
% C2=[ Cd(1,:);Cd(3:end,:)];
% C2=Cd(2,:);
C2o=Cd(3,:);
Fd3=[1.0e-4;1.0e-4;1e-4;1.0e-4;1e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1];
% Fd3=[1; 1;1.0e-4;1;1];
% C3=[Cd(1:2,:);Cd(end,:)];
% C3=Cd(3,:);
C3o=Cd(4,:);
% Fd4=[1.0e-4;1.0e-4;1.0e-4;1.0e-4;1];

% Fd=eye(4);
%Otra posibilidad
% Fd1=[1.0e-4;1;1;1;1];
% C1=Cd(2:end,:);   %Sin la entrada de de i1
% Fd2=[1;1.0e-4;1;1;1];
% C2=[ Cd(1,:);Cd(3:end,:)]; %Sin la entrada de de i2
% Fd3=[1;1;1.0e-4;1;1];
% C3=[Cd(1:2,:);Cd(end,:)]; %Sin la entrada de de i3
% Fd4=[1;1;1;1;1e-4];
% C4=Cd(1,:);
% C4=Cd(1:end-1,:); %Sin la entrada de de tension en la carga


%UIO2 para el ataque del sensor 2 eliminamos esa fila de la matriz C
Fd4=[1e-4;1e-4;1e-4;1;1e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
C4o=Cd(1,:);
Fd5=[1e-4;1e-4;1e-4;1e-4;1e-4;1;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
C5o=Cd(3,:);
Fd6=[1e-4;1e-4;1e-4;1e-4;1e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1];
C6o=Cd(4,:);

%UIO3 para el ataque del sensor 3 eliminamos esa fila de la matriz C
Fd7=[1e-4;1e-4;1e-4;1;1e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
C7o=Cd(1,:);
Fd8=[1e-4;1e-4;1.0e-4;1.0e-4;1;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
C8o=Cd(2,:);
Fd9=[1e-4;1e-4;1e-4;1e-4;1e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1];
C9o=Cd(4,:);

%UIO4 para el ataque del sensor 4 eliminamos esa fila de la matriz C
Fd10=[1e-4;1e-4;1e-4;1;1e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
C10o=Cd(1,:);
Fd11=[1e-4;1e-4;1.0e-4;1.0e-4;1;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
C11o=Cd(2,:);
Fd12=[1e-4;1e-4;1e-4;1e-4;1e-4;1;1.0e-4;1.0e-4;1.0e-4;1.0e-4;1.0e-4];
C12o=Cd(3,:);

% UIO para medida 1
[F1,T1,K1U,H1]=uio_linear (Ad,Bd,C1o,Fd1);
[F2,T2,K2U,H2]=uio_linear (Ad,Bd,C2o,Fd2);
[F3,T3,K3U,H3]=uio_linear (Ad,Bd,C3o,Fd3);
% UIO para medida 2
[F4,T4,K4U,H4]=uio_linear (Ad,Bd,C4o,Fd4);
[F5,T5,K5U,H5]=uio_linear (Ad,Bd,C5o,Fd5);
[F6,T6,K6U,H6]=uio_linear (Ad,Bd,C6o,Fd6);
% UIO para medida 3
[F7,T7,K7U,H7]=uio_linear (Ad,Bd,C7o,Fd7);
[F8,T8,K8U,H8]=uio_linear (Ad,Bd,C8o,Fd8);
[F9,T9,K9U,H9]=uio_linear (Ad,Bd,C9o,Fd9);
% UIO para medida 4
[F10,T10,K10U,H10]=uio_linear (Ad,Bd,C10o,Fd10);
[F11,T11,K11U,H11]=uio_linear (Ad,Bd,C11o,Fd11);
[F12,T12,K12U,H12]=uio_linear (Ad,Bd,C12o,Fd12);

% Matrices del sistema desde el inversor hacia la carga sin el controlador
% A=[-R1/L1 zeros(1,6) -1/L1 zeros(1,3);
%     0 -R2/L2 zeros(1,6) -1/L2 0 0;
%     zeros(1,2) -R3/L3 zeros(1,6) -1/L3 0;
%     zeros(1,3) -R4/L4 zeros(1,3) 1/L4 0 0 -1/L4;
%     zeros(1,4) -R5/L5 zeros(1,3) 1/L5 0 -1/L5;
%     zeros(1,5) -R6/L6 zeros(1,3) 1/L6 -1/L6;
%     zeros(1,6) -R/L zeros(1,3) 1/L;
%     1/C1 zeros(1,2) -1/C1 zeros(1,7);
%     0 1/C2 0 0 -1/C2 zeros(1,6);
%     0 0 1/C3 0 0 -1/C3 zeros(1,5);
%     zeros(1,3) 1/Cl 1/Cl 1/Cl -1/Cl zeros(1,3) -1/(Cl*RL)]; 
% B=[1/L1 0 0;
%    0 1/L2 0;
%    0 0 1/L3;
%    zeros(8,3)];
% C11=[zeros(1,3) 1 zeros(1,7)]; %Salida del BIO
% C22=[zeros(1,4) 1 zeros(1,6)]; %Salida del gene
% C33=[zeros(1,5) 1 zeros(1,5)]; %Salida del Diesel
% C44=[zeros(1,10) 1];
% C=[C11; C22; C33;C44];
% D=zeros(4,3);
% D1=zeros(1,3);
% D3=zeros(1,3);
% D2=zeros(1,3);
% 
% sis=ss(A,B,C,D);

clc


%%%Funciones de transferencia
%  h=tf([RL*L RL*R],[Cl*RL*L  (R*RL*Cl+L) RL+R]);
% h2=tf(1,conv([L1 R1],[C1*L4 R4*C1 1])+[0 0 L4 R4]);
% h3=tf(1,conv([L2 R2],[C2*L5 R5*C2 1])+[0 0 L5 R5]);
% h4=tf(1,conv([L3 R3],[C3*L6 R6*C3 1])+[0 0 L6 R6]);
