close all
clear
clc

n=-50:50

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

[no yo] = konvolusi(x,h,n);
figure
stem(no,yo,'.')
xlim([-20 20])

