function FilPop = filterBound(Population,Bound)
    NIndividu = max(size(Population));
    NVariant = min(size(Population));
    FilPop = zeros(NIndividu,NVariant);
    for i = 1:NIndividu
        for ii = 1:NVariant
            if(Population(i,ii)<Bound(ii,1))
                FilPop(i,ii) = Bound(ii,1);
            elseif (Population(i,ii) > Bound(ii,2) )
                FilPop(i,ii) = Bound(ii,2);
            else
                FilPop(i,ii) = Population(i,ii);
            end
        end
    end
end

