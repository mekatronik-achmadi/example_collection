function data = ProcessEchos(bdata,sdata,s,dmax,ndelay)

[nTx nRx] = size(bdata);

for tx = 1:nTx
    for rx = 1:nRx %correlate background and scene data
        cback{tx,rx} = processData(bdata{tx,rx}',s,0,dmax/343);
        cdata{tx,rx} = processData(sdata{tx,rx}',s,0,dmax/343);
        data{tx,rx} = cdata{tx,rx}-cback{tx,rx}; %account for hardware delays
        data{tx,rx} = data{tx,rx}(ndelay:length(data{tx,rx}));
    end
end

end

