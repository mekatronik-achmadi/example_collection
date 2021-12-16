function y=toFouImag(Fs,x)

n=0:1/Fs:1;
N=2^nextpow2(length(x));
m=(-N/2):(N/2)-1;
w=2*pi*m*Fs/N;
yall=(1/N)*x*exp(1i*w'*n);
y=imag(yall);

%plot(n,y)