function [s seq sequence Ns] = MakePNWaveform(T,N,alpha,fs)
%generate Maximum Length Sequence of length 255 (2ˆ8−1)

len = T*fs;

if N == 18; taps=[0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1]; end;
if N == 17; taps=[0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1]; end;
if N == 16; taps=[0 0 0 1 0 0 0 0 0 0 0 0 1 0 1 1]; end;
if N == 15; taps=[0 0 0 0 0 0 0 0 0 0 0 0 0 1 1]; end;
if N == 14; taps=[0 0 0 1 0 0 0 1 0 0 0 0 1 1]; end;
if N == 13; taps=[0 0 0 0 0 0 0 0 1 1 0 1 1]; end;
if N == 12; taps=[0 0 0 0 0 1 0 1 0 0 1 1]; end;
if N == 11; taps=[0 0 0 0 0 0 0 0 1 0 1]; end;
if N == 10; taps=[0 0 0 0 0 0 1 0 0 1]; end;
if N == 9; taps=[0 0 0 0 1 0 0 0 1]; end;
if N == 8; taps=[0 0 0 1 1 1 0 1]; end;
if N == 7; taps=[0 0 0 1 0 0 1]; end;
if N == 6; taps=[0 0 0 0 1 1]; end;
if N == 5; taps=[0 0 1 0 1]; end;
if N == 4; taps=[0 0 1 1]; end;
if N == 3; taps=[0 1 1]; end;

M = 2^N-1; m = ones(1,N);
regout = zeros(1,M);
for ind = 1:M
    buf = mod(sum(taps.*m),2);
    m(2:N) = m(1:N-1);
    m(1)=buf;
    regout(ind) = m(N);
end
comp = ~ regout;
sequence = regout - comp;

%%Create SRRC pulse for shaping
U = fix(len/(2^N-1)); %upsample factor
Ns = U;
g = SRRC(4,alpha,U);
g = g./max(g); %normalize to 1
x = upsample(sequence,U);
seq = [zeros(1,4*U) x];

s = conv(x,g);

s = [s zeros(1,2^(ceil(log2(len)))-length(s))];

end

