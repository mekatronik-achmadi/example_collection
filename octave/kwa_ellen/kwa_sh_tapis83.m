%===================================================================================================================================
% Killer Whale Optimization Algorithm
% Author        : Totok Ruki Biyanto (TRB)
% Email         : trb@ep.its.ac.id; trbiyanto@gmail.com;
%===================================================================================================================================

clc;
clear;
close all;

%% Problem Definition
Dimension = 4;          % dimensi diganti sesuai dengan jumlah variabel yang dioptimasi
%Constraint

UB = [850 2600 0.8 0.2];% Upper Bounds diganti sesuai dengan constraint fungsi objektif
LB = [750 2500 0 0];% Lower Bounds diganti sesuai dengan constraint fungsi objektif

CostFunction=@(x) (model_ellen(x));        % Cost Function %Model

nVar=Dimension;            % Number of Decision Variables

VarSize=[1 nVar];   % Size of Decision Variables Matrix

VarMin=LB;         % Lower Bound of Variables
VarMax=UB;         % Upper Bound of Variables


%% PSO Parameters

MaxIt=20;      % Maximum Number of Iterations

nPop=100;        % Population Size (Swarm Size)
nTeam = 10;      % Team (Number of Leader)
TeamSize = [];
for i=1:nTeam-1
    TeamSize(i) = ceil(nPop/nTeam);
end
TeamSize(nTeam) = nPop - sum(TeamSize);

% PSO Parameters
w=1;            % Inertia Weight
wdamp=0.99;     % Inertia Weight Damping Ratio
c1=1.5;         % Personal Learning Coefficient
c2=2.0;         % Global Learning Coefficient
c3=1.0;         % Leader Influence Coefficient

Porder=3;       % order of Polynomial


% If you would like to use Constriction Coefficients for PSO,
% uncomment the following block and comment the above set of parameters.

% % Constriction Coefficients
% phi1=2.05;
% phi2=2.05;
% phi=phi1+phi2;
% chi=2/(phi-2+sqrt(phi^2-4*phi));
% w=chi;          % Inertia Weight
% wdamp=1;        % Inertia Weight Damping Ratio
% c1=chi*phi1;    % Personal Learning Coefficient
% c2=chi*phi2;    % Global Learning Coefficient

% Velocity Limits
VelMax=0.1*(VarMax-VarMin);
VelMin=-VelMax;

%% Initialization

initial_whales.Position=[];
initial_whales.Cost=[];
initial_whales.Velocity=[];
initial_whales.Best.Position=[];
initial_whales.Best.Cost=[];

whales=repmat(initial_whales,nPop,1);
leader_whales=repmat(initial_whales,nTeam,1);
leader_whales_poly = [];
leader_whales_std = [];
%temp_whales = [];
%tempeval_whales = [];

GlobalBest.Cost=inf;

for i=1:nPop
    
    % Initialize Position
    whales(i).Position=unifrnd(VarMin,VarMax,VarSize);
    
    % Initialize Velocity
    whales(i).Velocity=zeros(VarSize);
    
    % Evaluation
    whales(i).Cost=CostFunction(whales(i).Position);
    % temp_whales(:, i) = whales(i).Position;
    
end
% tempeval_whales(1:nPop) = whales.Cost(1:nPop);
for i=1:nPop 
%     whales(i).Cost = tempeval_whales(i);
    % Store data for polyfit
    for j=1:Dimension
        whalesPosition(i,j) =  whales(i).Position(j);
    end
    whalesPosition(i,Dimension+1) = whales(i).Cost;
    
    % Update Personal Best
    whales(i).Best.Position=whales(i).Position;
    whales(i).Best.Cost=whales(i).Cost;
    
    % Update Global Best
    if whales(i).Best.Cost<GlobalBest.Cost
        
        GlobalBest=whales(i).Best;
        
    end
    
end


temp_whales = [];
tempeval_whales = [];
for t=1:nTeam
    for j=1:Dimension
        leader_whales_std(t,j) = std2(whalesPosition(((t-1)*ceil(nPop/nTeam))+1:((t-1)*ceil(nPop/nTeam))+TeamSize(t),j));
        buffer = polyfit(whalesPosition(((t-1)*ceil(nPop/nTeam))+1:((t-1)*ceil(nPop/nTeam))+TeamSize(t),j),whalesPosition(((t-1)*ceil(nPop/nTeam))+1:((t-1)*ceil(nPop/nTeam))+TeamSize(t),Dimension+1),Porder);
        leader_whales_poly(t,:,j) = buffer;
        
        syms x;
        fun = matlabFunction(poly2sym(buffer));
        leader_whales(t).Position(j) = fminsearch((fun),0);
        
        leader_whales(t).Position(j) = min(leader_whales(t).Position(j), UB(j));
        leader_whales(t).Position(j) = max(leader_whales(t).Position(j), LB(j));
    end
    temp_whales(:, t) = leader_whales(t).Position;
    
end
% tempeval_whales = CostFunction(temp_whales);
for t=1:nTeam
    % leader_whales(t).Cost = tempeval_whales(t);
    leader_whales(t).Cost = CostFunction(leader_whales(t).Position);
end

BestCost=zeros(MaxIt,1);

%% PSO Main Loop

for it=1:MaxIt
    
    for t=1:nTeam
        
        temp_whales = [];
        %tempeval_whales = [];
        
        for i=((t-1)*ceil(nPop/nTeam))+1:((t-1)*ceil(nPop/nTeam))+TeamSize(t)
            % make into cluster
            % each cluster will have it's own leader
            % each member of cluters should chate their own leader
            % leader get information from their member, and draw a polynomial
            % equation to map the scanned area
            
            % Update Velocity
            % Leader or GlobalBest
            if GlobalBest.Cost < leader_whales(t).Cost   % min
                ct3 = 0;
                ct2 = c2;
            else
                ct3 = c3;
                ct2 = 0;
            end
            
            whales(i).Velocity = w*whales(i).Velocity ...
                +c1*rand(VarSize).*(whales(i).Best.Position-whales(i).Position) ...
                +ct2*rand(VarSize).*(GlobalBest.Position-whales(i).Position) ...
                +ct3*rand(VarSize).*(leader_whales(t).Position);
            
            % Apply Velocity Limits
            whales(i).Velocity = max(whales(i).Velocity,VelMin);
            whales(i).Velocity = min(whales(i).Velocity,VelMax);
            
            % Update Position
            whales(i).Position = whales(i).Position + whales(i).Velocity;
            
            % Velocity Mirror Effect
            IsOutside=(whales(i).Position<VarMin | whales(i).Position>VarMax);
            whales(i).Velocity(IsOutside)=-whales(i).Velocity(IsOutside);
            
            % Apply Position Limits
            whales(i).Position = max(whales(i).Position,VarMin);
            whales(i).Position = min(whales(i).Position,VarMax);
            
            temp_whales(:, i) = whales(i).Position;
        end
        
        % tempeval_whales = CostFunction(temp_whales);
        
        for i=((t-1)*ceil(nPop/nTeam))+1:((t-1)*ceil(nPop/nTeam))+TeamSize(t)
                
            % Evaluation
            whales(i).Cost = CostFunction(whales(i).Position);
            % whales(i).Cost = tempeval_whales(i);
            
            % Store data for polyfit
            for j=1:Dimension
                whalesPosition(i,j) =  whales(i).Position(j);
            end
            whalesPosition(i,Dimension+1) = whales(i).Cost;
            
            % Update Personal Best
            if whales(i).Cost<whales(i).Best.Cost
                
                whales(i).Best.Position=whales(i).Position;
                whales(i).Best.Cost=whales(i).Cost;
                
                % Update Global Best
                if whales(i).Best.Cost<GlobalBest.Cost
                    
                    GlobalBest=whales(i).Best;
                    
                end
                
            end
            
        end
        
    end
    
    polycheck = 0;
    leader_whales_poly = [];
    temp_whales = [];
    tempeval_whales = [];
    for t=1:nTeam
        for j=1:Dimension
            leader_whales_std(t,j) = std2(whalesPosition(((t-1)*ceil(nPop/nTeam))+1:((t-1)*ceil(nPop/nTeam))+TeamSize(t),j));
            if leader_whales_std < 0.01
                polycheck = 1;
            else
                buffer = polyfit(whalesPosition(((t-1)*ceil(nPop/nTeam))+1:((t-1)*ceil(nPop/nTeam))+TeamSize(t),j),whalesPosition(((t-1)*ceil(nPop/nTeam))+1:((t-1)*ceil(nPop/nTeam))+TeamSize(t),Dimension+1),Porder);
                leader_whales_poly(t,:,j) = buffer;
                
                if max(isnan(buffer)) < 1
                    syms x;
                    fun = matlabFunction(poly2sym(buffer));
                    leader_whales(t).Position(j) = fminsearch((fun),0);
                end
                leader_whales(t).Position(j) = min(leader_whales(t).Position(j), UB(j));
                leader_whales(t).Position(j) = max(leader_whales(t).Position(j), LB(j));
            end
            
        end
%         temp_whales(:, t) = leader_whales(t).Position;
    end
    % tempeval_whales = CostFunction(temp_whales);
    for t=1:nTeam
        % leader_whales(t).Cost = tempeval_whales(t);
        leader_whales(t).Cost = CostFunction(leader_whales(t).Position);
    end
    
    BestCost(it)=GlobalBest.Cost;
    
    disp(['Iteration ' num2str(it) ': Best Cost = ' num2str(BestCost(it)) ': Datacheck = ' num2str(polycheck)]);
    
    w=w*wdamp;
    
end

BestSol = GlobalBest;

%% Results
min_variable_design = BestSol.Position(1,:);
min_objective_function = BestSol.Cost(1,:);
figure;
%plot(BestCost,'LineWidth',2);
semilogy(BestCost,'LineWidth',2);
title('Grafik Nilai Minimum KWA','color','b')
xlabel('Jumlah Iterasi');
ylabel('Nilai Fungsi Obyektif');
grid on;