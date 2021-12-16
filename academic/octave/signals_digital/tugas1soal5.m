clear
clc
close all

t=-6:0.001:6;
t0=1;

y=delta(t-t0);

figure(5)
plot(t,y,'b','Linewidth',2)
axis([-6 6 -1 2])
xlabel('t')
ylabel('f(t)')