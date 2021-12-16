% Algoritma Genetika untuk memaksimalkan fungsi dengan 2 variabel
% Fungsi (x,y) pada Persamaan Perpindahan Panas HE dengan variabel diameter dalam tube dan sudut baffle

function [BestV,BestF] = geneticAlgorithm(Number_Individu,Number_Variant,Number_Iteration,Bound_Variant,desire_function,objective_function)
    % Membangkitkan (inisialisasi) populasi
    Population = create_population( [Number_Individu,Number_Variant],Bound_Variant);
    PopulationS = Population;

    BestF_plot = NaN(1,Number_Iteration);
    Iteration_plot = NaN(1,Number_Iteration);
    for Iteration = 1:Number_Iteration
        Population = filterBound(Population,Bound_Variant);
        Fitness = objective_function(Population);
        [FitnessBest,FitnessBestPos] = desire_function(Fitness);
        FitnessMin = min(Fitness);
        if( mod(Number_Individu,2) == 0 )
            StartIter = 6;
            PopulationS(1,:) = Population(FitnessBestPos,:);
            PopulationS(2,:) = Population(FitnessBestPos,:);
            PopulationS(3,:) = Population(FitnessBestPos,:);
            PopulationS(4,:) = Population(FitnessBestPos,:);
            PopulationS(5,:) = Population(FitnessBestPos,:);
        else
            StartIter = 5;
            PopulationS(1,:) = Population(FitnessBestPos,:);
            PopulationS(2,:) = Population(FitnessBestPos,:);
            PopulationS(3,:) = Population(FitnessBestPos,:);
            PopulationS(4,:) = Population(FitnessBestPos,:);
        end

    % Menghitung nilai fitnessnya
        FitnessNormal = Fitness - FitnessMin;
        for IterInd = StartIter:2:Number_Individu
            for IterVar = 1:Number_Variant
                Parent1 = selection(FitnessNormal);
                Parent2 = selection(FitnessNormal);
                if( rand() < 0.8 )
                    Child = cross_over( PopulationS (Parent1,IterVar),PopulationS(Parent2,IterVar));
                    PopulationS(IterInd,IterVar) = Child(1);
                    PopulationS(IterInd+1,IterVar) = Child(2);
                else
                    PopulationS(IterInd,IterVar) = PopulationS(Parent1,IterVar);
                    PopulationS(IterInd+1,IterVar) = PopulationS(Parent2,IterVar);
                end
            end
        end
        Half = round( Number_Individu/2 );
        for IterInd = 1:Half
            for IterVar = 1:Number_Variant
                RandomValue = 4+ceil(rand()*Number_Individu );
                PopulationS(RandomValue,IterVar) = Bound_Variant (IterVar,1) + (Bound_Variant(IterVar,2)-Bound_Variant (IterVar,1))*rand();
            end
        end

        Population = PopulationS;
        BestF_plot(Iteration) = FitnessBest;
        Iteration_plot(Iteration) = Iteration;
        plot(Iteration_plot,BestF_plot,'LineWidth',3);
        title(['Genetic Algorithm Optimization''( Overall Heat Transfer Maximum :' num2str(FitnessBest) ')']);
        xlabel('Number of Iteration');
        ylabel('Overall Heat Transfer(W/m2.C)');
        drawnow;
    end

    BestF = FitnessBest;
    BestV = Population(FitnessBestPos,:);
    [~] = perpindahan_panas3(BestV(1),BestV(2));

end
