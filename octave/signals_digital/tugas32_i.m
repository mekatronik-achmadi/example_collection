close all
clear
clc

t=-4:0.001:4;
t2=2*min(t):0.001:2*max(t);
a=3;
b=2;

x=a*t+b;
h=(4/5)*(unitstep(t)-unitstep(t-1))+(-1/3)*delta(t-2);

figure
subplot(2,1,1)
plot(t,x)
 
subplot(2,1,2)
plot(t,h)
 
y=conv(x,h)
figure
plot(t2,y,'color','r')
