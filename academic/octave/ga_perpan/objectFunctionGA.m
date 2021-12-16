% Mendefinisikan parameter dari permasalahan yang akan diselesaikan

function Fitness=objectFunctionGA(MatVariables)
    NVariant = min(size(MatVariables));
    NIndividu = max(size(MatVariables));
    Fitness = zeros(NIndividu,1);
    switch(NVariant)
        case 2
        x = MatVariables(:,1);
        y = MatVariables(:,2);
        for i=1:NIndividu
            Fitness(i) = perpindahan_panas3(x(i),y(i));
        end
    end
end