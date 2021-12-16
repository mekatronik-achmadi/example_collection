% Proses Seleksi
function Index = selection(Fitness)
    SumFitnessValue = sum(Fitness);
    CumFitnessValue = 0;
    RandomValue = rand();
    NumberFitness = max(size(Fitness));
    I = 2;
    while( I <= NumberFitness )
        CumFitnessValue = CumFitnessValue + Fitness(I);
        Fraction = CumFitnessValue / SumFitnessValue;
        if( Fraction > RandomValue )
            Index = I;
            break;
        else
            Index = NumberFitness;
        end
        I = I + 1;
    end
end

