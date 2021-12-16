clear
clc
close all
 
t=-4:0.001:4;
t2=2*min(t):0.001:2*max(t);
a=1;
d=1/2;

x=(-a.*abs(t)+a).*(unitstep(t+1)-unitstep(t-1));
h=(1/d)*delta(t+d/2)+(-1/d)*delta(t-d/2);

figure
subplot(2,1,1)
plot(t,x)
 
subplot(2,1,2)
plot(t,h)
 
y=conv(x,h);
figure
plot(t2,y,'color','r')
