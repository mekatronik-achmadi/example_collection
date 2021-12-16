clear
clc
close all

t=-7:0.001:7;
t0=2;

y=delta(-t+t0);

figure(5)
plot(t,y,'color',[0 100 0]/255,'Linewidth',2)
axis([-7 7 -1 1.1])
xlabel('t')
ylabel('f(t)')