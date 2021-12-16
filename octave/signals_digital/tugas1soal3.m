clear
clc
close all

t=-15:0.001:15;
t0=5;

y=-unitstep(t+t0);

figure(3)
plot(t,y,'color', [0 0 255]/255,'Linewidth',2)
axis([-15 15 -1.2 1.2])
xlabel('t')
ylabel('f(t)')