clear 
clc
close all

fig = openfig('corriente1.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')
x1m = dataObjs(1).YData;
x1o = dataObjs(2).YData;
t = dataObjs(1).XData;
fig = openfig('corriente2.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')
x2m = dataObjs(1).YData;
x2o = dataObjs(2).YData;
t = dataObjs(1).XData;
fig = openfig('corriente3.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')
x3m = dataObjs(1).YData;
x3o = dataObjs(2).YData;
t = dataObjs(1).XData;
fig = openfig('tension.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')
x4m = dataObjs(1).YData;
x4o = dataObjs(2).YData;
t = dataObjs(1).XData;
% fig = openfig('duty_c.fig');
% fig = gcf;
% dataObjs = findobj(fig,'-property','YData')  %%Entradas del sistema
% v3 = dataObjs(1).YData;
% v2= dataObjs(2).YData;
% v1 = dataObjs(3).YData;

%%Filtrado/Suavizado de algunas señales
order = 3;
framelen = 11;
xm2f = sgolayfilt(x2m,order,framelen);
xo2f = sgolayfilt(x2o,order,framelen);
r=xm2f-x2o;

close all
subplot(3,1,1)
grid on
plot(t,xm2f,t,xo2f)
xlim([180 260])
ylim([-70 70])
subplot(3,1,2)
grid on
plot(t,x2m,t,x2o)
xlim([180 260])
ylim([-70 70])

subplot(3,1,3)
plot(t,r)
xlim([100 680])

figure
subplot(4,1,1)
plot(t,x1o)
hold on
plot(t,x1m)
ylabel('x_{1} [A]')
xlabel('Tiempo(s)')
grid on
xlim([100 680])
legend('Estado 1 observado','Estado 1 medido')
% figure
subplot(4,1,2)
plot(t,x2o)
hold on
plot(t,x2m)
ylabel('x_{2} [A]')
xlabel('Tiempo(s)')
grid on
xlim([100 680])
legend('Estado 2 observado','Estado 2 medido')
% figure
subplot(4,1,3)
plot(t,x3o)
hold on
plot(t,x3m)
grid on
xlim([100 680])
ylabel('x_{3} [A]')
xlabel('Tiempo(s)')
legend('Estado 3 observado','Estado 3 medido')
% figure
subplot(4,1,4)
plot(t,x4o)
hold on
plot(t,x4m)
grid on
xlim([100 680])
ylabel('x_{4} [V]')
xlabel('Tiempo(s)')
legend('Estado 4 observado','Estado 4 medido')

figure
subplot(4,1,1)
plot(t,x1o-x1m)
xlim([100 680])
grid on
% legend('Residual de x1')
ylabel('Residue x_{1} [A]')
xlabel('Tiempo(s)')

% figure
subplot(4,1,2)
plot(t,x2o-x2m)
xlim([100 680])
ylabel('Residue x_{2} [A]')
xlabel('Tiempo(s)')
grid on
% legend('Residual de x2')
% figure
subplot(4,1,3)
plot(t,x3o-x3m)
xlim([100 680])
ylabel('Residue x_{3} [A]')
xlabel('Tiempo(s)')
grid on
% legend('Residual de x3')
% figure
subplot(4,1,4)
plot(t,x4o-x4m)
xlim([100 680])
ylabel('Residue x_{4} [V]')
xlabel('Tiempo(s)')
grid on

clc


% posi=find(t==500);
% posf=find(t==700);
% t1=t(posi:posf);
% x1o=x1o(posi:posf);
% x1m=x1m(posi:posf);
% rx1=rx1(posi:posf);
rx1=x1o-x1m;
posi=find(t==500);
posf=find(t==700);
t2=t(posi:end);
% x2o=x2o(posi:posf);
% x2m=x2m(posi:posf);
% rx2=rx2(posi:posf);
rx2=x2o(posi:end)-x2m(posi:end);
% x3m=x3m(posi:posf);
% x3o=x3o(posi:posf);
% posi=find(t==300);
% posf=find(t==400);
% t4=t(posi:posf);
% x4m=x4m(posi:posf);
% x4o=x4o(posi:posf);
rx3=x3o-x3m;
rx4=x4o-x4m;



% rx3=rx3(posi:posf);
% rx4=rx4(posi:posf);

figure
subplot(4,1,1)
plot(t,rx1)
grid on
% legend('Residual de x1')
ylabel('Residue x_{1} [A]')
xlabel('Tiempo(s)')

% figure
subplot(4,1,2)
plot(t2,rx2)
ylabel('Residue x_{2} [A]')
xlabel('Tiempo(s)')
grid on
% legend('Residual de x2')
% figure
subplot(4,1,3)
plot(t,rx3)
ylabel('Residue x_{3} [A]')
xlabel('Tiempo(s)')
grid on
% legend('Residual de x3')
% figure
subplot(4,1,4)
plot(t,rx4)
ylabel('Residue x_{4} [V]')
xlabel('Tiempo(s)')
grid on
% legend('Residual de x4')