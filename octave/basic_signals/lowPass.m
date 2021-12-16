function y=lowPass(Fs,x,wcut)

n=0:1/Fs:1;
N=2^nextpow2(length(x));
m=(-N/2):(N/2)-1;
w=2*pi*m*fs/N;
thefilter=w/(2*pi)>-wcut & w/(2*pi)<wcut;
yall=(1/N)*(x.*thefilter)*exp(1i*w'*n);
y=real(yall);

%plot(w/(2*pi), thefilter)
%xlim([-A A])

%plot(n,y)