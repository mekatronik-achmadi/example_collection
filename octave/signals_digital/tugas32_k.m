close all
clear
clc

t=-4:0.001:4;
t2=2*min(t):0.001:2*max(t);

x=SQUARE(2*pi*0.5*(t-0.5))
h=(1-t).*(unit_step(t)-unit_step(t-1));

figure
subplot (2,1,1)
plot (t,x,'color','r')

subplot (2,1,2)
plot (t,h,'color','r')

y=conv(x,h);
figure
plot (t2,y)
