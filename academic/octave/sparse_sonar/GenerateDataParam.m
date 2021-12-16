function data_parameters = GenerateDataParam(tx,rx,max_n)

data_parameters.G = length(tx)*length(rx);

li = 1; 
for ix = 1:length(tx)
    for iy = 1:length(rx)
        data_parameters.g(li,:) = [ix iy];
        data_parameters.gpos(li,:) = [tx(ix) rx(iy)];
        li = li + 1;
    end
end

data_parameters.nmax = max_n;
data_parameters.TM = randn(max_n,max_n);

end

