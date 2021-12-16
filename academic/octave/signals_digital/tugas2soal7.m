clear
clc
close all

t=-2:0.2:3;
t0=2;

y=delta(t)-2*delta(t-1)+delta(t-2);

figure(5)
stem(t,y,'color',[200 40 10]/255,'Linewidth',2)
axis([-2 3 -1 2])
xlabel('n')
ylabel('f[n]')