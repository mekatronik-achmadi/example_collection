close all
clear
clc

t=-10:0.001:10;
t2=2*min(t):0.001:2*max(t);

x = zeros(size(t));
for i=1:length(t)
    if t(i)<0
        x(i)=exp(t(i));
    elseif t(i)>0
        x(i)=exp(5*t(i))-2*exp(-t(i));
    end
end
h=unit_step(t)-unit_step(t-1);

figure
subplot (2,1,1)
plot (t,x)

subplot (2,1,2)
plot (t,h)

y=conv(x,h);
figure
plot(t2,y,'color','r')
