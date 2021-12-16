clear
clc
close all

t=-6:0.001:4;
t0=2;

y=unitstep(-t+t0);

figure(4)
plot(t,y,'r','Linewidth',2)
axis([-6 4 -1 3])
xlabel('t')
ylabel('f(t)')