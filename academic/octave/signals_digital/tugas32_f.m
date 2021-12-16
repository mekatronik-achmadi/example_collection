close all
clear
clc

t=-4:0.001:4;
t2=2*min(t):0.001:2*max(t);

x=sin(pi*t);
h=2*(unit_step(t-1)-unit_step(t-3));

figure
subplot (2,1,1)
plot (t,x)

subplot (2,1,2)
plot (t,h)

y=conv(x,h);
figure
plot(t2,y,'color','r')
