function [pixelgrid image] = Backproject(cdata, Tx, Rx, L, N)

c = 343;
fs = 96000;

nTx = length(Tx);
nRx = length(Rx);

R = (c/fs)/(L/N);

fprintf('Resampling Data...');

for tx = 1:nTx
    for rx = 1:nRx
        len = length(cdata{tx,rx});
        cdata{tx,rx} = interp1(1:len,cdata{tx,rx},linspace(1,len,fix(len*R))); 
    end
end

fprintf(' Complete.\n');

if (mod(N,2)==0) N = N-1; end

pixpos = (linspace(-L/2,L/2,N)'*ones(1,N))'+linspace(-L/2*i,L/2*i,N)'*ones(1,N);

image = zeros(N,N);

fprintf('Constructing Image: ');
tic;
mark = 0;
for x=1:N
    t=toc;
    if (floor(t)>mark)
        fprintf('%d%%, ',ceil(x/N*100));
        mark = mark + 1;
    end
    
    for y=1:N
        for rx=1:nRx
            d = abs(Tx(tx)-pixpos(x,y))+abs(Rx(rx)-pixpos(x,y));
            n = fix(R*d/c*fs);
            if (n <= length(cdata{tx,rx}))
                image(x,y) = image(x,y) + cdata{tx,rx}(n); 
            end
        end
    end
end

fprintf('Completed. \n');

image = image./max(max(image));
pixelgrid = pixpos;

end