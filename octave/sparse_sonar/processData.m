function cr = processData(r,s,Tstart,Tmax)

fs = 96000;
c = 343;

M = length(s);
N = length(r);

nstart = fix(Tstart*fs);
nmax = fix(Tmax*fs);

if (length(r) < length(s))
    r = [r zeros(1,length(s)-length(r))]; 
end

cr = real(ifft(fft(r,N+M-1).*fft(fliplr(s),N+M-1)));
cr = cr(M:length(cr));
cr = cr((nstart+1):length(cr));

cr = cr(1:nmax);

end

