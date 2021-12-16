clear
clc
close all

a=0.125
t=-10:0.001:10;

y=a*t;

figure(5)
plot(t,y,'color',[0 0 255]/255,'Linewidth',2)
axis([-10 10 -1 1])
xlabel('t')
ylabel('f(t)')