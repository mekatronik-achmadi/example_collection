function y=toFou(Fs,x)

n=0:1/Fs:1;
N=2^nextpow2(length(x));
m=(-N/2):(N/2)-1;
w=2*pi*m*Fs/N;
y=x*exp(-1i*n'*w);

%plot (w/(2*pi),abs(y))
