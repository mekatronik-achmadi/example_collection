function y=toFouSer(Fs,N,a0,a1,b1)

t=-N:1/Fs:N;
n=1/N;
an=a1*sin(pi*n)./(pi*n);
bn=b1*(sin(pi*n/2)).^2./(pi*n);

y=(a0/2)+an*cos(pi*n'*t)+bn*sin(pi*n'*t);

%plot(t,y)
