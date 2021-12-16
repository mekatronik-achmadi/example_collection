function [data cdata]=SimulateEchos(Rfs, Tx, Rx, s, fs)
%Code to Simulate ideal data echo

c = 343; %speed of sound, assumed constant
nTx = length(Tx); nRx = length(Rx); nRfs = length(Rfs);

%calculate the distance between each reflector and Receiver, each %reflector and transmitter respectively
for r = 1:length(Rfs)
    dTxR(r,:) = abs(Tx-Rfs(r));
    dRxR(r,:) = abs(Rx-Rfs(r));
end

N=nTx*nRx;

fprintf('Simulating Data...',N);
for tx = 1:nTx
    fprintf('.');
    for rx = 1:nRx
        d = (dTxR(:,tx)+dRxR(:,rx))';
        n = fix(d./c.*fs);
        data{tx,rx} = zeros(1,max(n));
        
        for rfs = 1:nRfs
            data{tx,rx}(n(rfs)) = data{tx,rx}(n(rfs)) + 1;
        end
    end
end

fprintf(' Complete.\n');

fprintf('Correlating Data...');
d = real(fftshift(ifft(fft(s).*fft(fliplr(s)))));
for tx = 1:nTx
    fprintf('.');
    for rx = 1:nRx
        zpaddata = [data{tx,rx} zeros(1,length(d)/2)];
        cd = real(ifft(fft(zpaddata,length(d)).*fft(d)));
        cdata{tx,rx} = cd(length(cd)/2:length(cd));
        cdata{tx,rx} = cdata{tx,rx}(1:(2*length(data{tx,rx})));
    end
end
fprintf(' Complete.\n');

end