function [A y]=MakeCSParameters(adata, ydata, dataparams, imageparams,fs)

c = 343;

L = imageparams.L;
N = imageparams.N;

G = dataparams.G;
gpos = dataparams.gpos;
nmax = dataparams.nmax;
keepsamples = dataparams.keepsamples;
T = dataparams.TM;

nEff = length(dataparams.keepsamples{1});

for k = 1:dataparams.G
    Adata{k} = adata.data{dataparams.g(k,1),dataparams.g(k,2)};
    if (length(Adata{k})<dataparams.nmax) Adata{k} = [Adata{k}
            zeros(1,length(dataparams.nmax-Adata{k}))];
    end
    
    Ydata{k} = ydata.data{dataparams.g(k,1),dataparams.g(k,2)};
    if (length(Ydata{k})<dataparams.nmax)
        Ydata{k} = [Ydata{k} zeros(1,length(dataparams.nmax-Ydata{k}))];
    end
end

pixpos = (linspace(-L/2,L/2,N)'*ones(1,N))'+linspace(-L/2*i,L/2*i,N)'*ones(1,N);
centerDistance = abs(gpos(:,1))+abs(gpos(:,2));

for g = 1:G
    xydelay{g} = fs/c*((abs(gpos(g,1)-pixpos)+abs(pixpos-gpos(g,2)))-centerDistance(g));
    pixvec = xydelay{g}(:,1);
    for n = 2:N 
        pixvec = [pixvec; xydelay{g}(:,n)]; 
    end
    delay{g} = pixvec; 
end

A = zeros(G*nEff,N^2); 
for g = 1:G
    FreqData{g} = fft(Adata{g}(1:nmax),nmax);
end

indexes = (nEff*(0:G))+1;

df = 1/(nmax*1/fs);
f = df*(1:nmax);

for pixel=1:N^2
    if (mod(pixel,fix(N^2/100))==0)
        fprintf('%d \n',pixel);
    end
    
    for g = 1:G
        tau = round(delay{g}(pixel))/fs;
        e = exp(j*2*pi.*f*-tau);
        FreqD = e.*FreqData{g};
        datapoints = T*real(ifft(FreqD))';
        datapoints = datapoints(1:length(round(keepsamples{g})));
        datapoints = datapoints./max(datapoints);
        A(indexes(g):(indexes(g+1)-1),pixel) = datapoints; 
    end
end

indexes = (nEff*(0:dataparams.G))+1;
for g=1:dataparams.G
    datapoints = (dataparams.TM*Ydata{g}(1:dataparams.nmax)');
    datapoints = datapoints(1:length(round(keepsamples{g})));
    datapoints = datapoints./max(datapoints);
    y(indexes(g):(indexes(g+1)-1),1) = datapoints;
end

end

