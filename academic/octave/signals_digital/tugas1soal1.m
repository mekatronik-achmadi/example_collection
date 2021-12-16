clear
clc
close all

t=-1:0.001:7;
t0=2;

y=unitstep(t-t0);

figure(1)
plot(t,y,'color', [0 160 70]/255,'Linewidth',2)
axis([-1 7 -0.2 1.5])
xlabel('t')
ylabel('f(t)')