function g = SRRC(N, alf, P, t_off)
%SRRC Create an oversampled square−root raised cosine pulse

if nargin==3, t_off=0; end;
k = -N*P + 1e-8 + t_off:N*P +1e-8 +t_off;

if alf==0, alf=1e-8; end;

g = 4*alf/sqrt(P)*(cos((1+alf)*pi*k/P)+sin((1-alf)*pi*k/P)./(4*alf*k/P))./(pi*(1-16*(alf*k/P).^2));

end

