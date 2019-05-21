clear 
clc
close all

fig = openfig('state1.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')
x1m = dataObjs(1).YData;
x1o = dataObjs(2).YData;
t = dataObjs(1).XData;
fig = openfig('state2.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')
x2m = dataObjs(1).YData;
x2o = dataObjs(2).YData;
t = dataObjs(1).XData;
fig = openfig('state3.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')
x3m = dataObjs(1).YData;
x3o = dataObjs(2).YData;
t = dataObjs(1).XData;
fig = openfig('state4.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')
x4m = dataObjs(1).YData;
x4o = dataObjs(2).YData;
t = dataObjs(1).XData;
fig = openfig('duty_c.fig');
fig = gcf;
dataObjs = findobj(fig,'-property','YData')  %%Entradas del sistema
v3 = dataObjs(1).YData;
v2= dataObjs(2).YData;
v1 = dataObjs(3).YData;
close all
% figure
plot(t,x1o)
hold on
plot(t,x1m)
grid on
legend('Estado 1 observado','Estado 1 medido')
figure
plot(t,x2o)
hold on
plot(t,x2m)
grid on
legend('Estado 2 observado','Estado 2 medido')
figure
plot(t,x3o)
hold on
plot(t,x3m)
grid on
legend('Estado 3 observado','Estado 3 medido')
figure
plot(t,x4o)
hold on
plot(t,x4m)
grid on
legend('Estado 4 observado','Estado 4 medido')

figure
subplot(3,1,1)
plot(t,v1)
subplot(3,1,2)
plot(t,v2)
subplot(3,1,3)
plot(t,v3)
hold on

%Procesando los datos para posteriormente realizar ajustes

posi=find(t==200);
posf=find(t==600);
t=t(posi:posf);
x1o=x1o(posi:posf);
x1m=x1m(posi:posf);
x2o=x2o(posi:posf);
x2m=x2m(posi:posf);
x3m=x3m(posi:posf);
x3o=x3o(posi:posf);
x4m=x4m(posi:posf);
x4o=x4o(posi:posf);
v1=v1(posi:posf);
v2=v2(posi:posf);
v3=v3(posi:posf);



% close all
figure
plot(t,x1o)
hold on
plot(t,x1m)
grid on
legend('Estado 1 observado','Estado 1 medido')
figure
plot(t,x2o)
hold on
plot(t,x2m)
grid on
legend('Estado 2 observado','Estado 2 medido')
figure
plot(t,x3o)
hold on
plot(t,x3m)
grid on
legend('Estado 3 observado','Estado 3 medido')
figure
plot(t,x4o)
hold on
plot(t,x4m)
grid on
legend('Estado 4 observado','Estado 4 medido')

figure
subplot(3,1,1)
plot(t,v1)
subplot(3,1,2)
plot(t,v2)
subplot(3,1,3)
plot(t,v3)
hold on