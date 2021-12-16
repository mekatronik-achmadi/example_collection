close all
clear
clc

n=-50:1:50;
n2=2*min(n):1:2*max(n);

x = ones(size(n));
h = zeros(size(n));
for i=1:length(n)
    if n(i)>=0
        h(i)=(1/2)^n(i);
    else
        h(i)=4^n(i);
    end
end

figure
subplot(2,1,1)
stem(n,x,'.')

subplot(2,1,2)
stem(n,h,'.')

y=conv(x,h);
figure
stem(n2,y,'.','color','r')
xlim([-20 20])


