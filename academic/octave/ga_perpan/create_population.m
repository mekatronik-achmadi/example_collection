function Population = create_population(Size_Population,Bound)
    NIndividu = Size_Population(1);
    NVariant = Size_Population(2);
    Population =zeros(NIndividu,NVariant);
    for i=1:NIndividu
        for ii=1:NVariant
            Population(i,ii) =Bound(ii,1) +(Bound(ii,2)-Bound(ii,1))*rand();
        end
    end
end

