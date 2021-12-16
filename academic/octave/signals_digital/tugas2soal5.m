clear
clc
close all

t=-6:0.4:6;
t0=4;

y=delta(t-t0);

figure(5)
stem(t,y,'color',[0 200 0]/255,'Linewidth',2)
axis([-6 6 -1 2])
xlabel('n')
ylabel('f[n]')