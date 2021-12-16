
%We assume u(k) = 0. We also let B = 0 and D = 0
A = [ 1 5 12.5; 0 1 5; 0 0 1];
B = [ 1 1 1]' ;
C = [1 0 0] ;
D = 0 ;
Q = 0.1; R = 900 ;
x0 = [1 1 1];
t = [ 0 : 100]' ; %we assume 101 time steps.
u = zeros( 1, 101); % this is the zero excitation
sys = ss( A, B, C, 0, -1); % ss generates the space-state model
y = lsim( sys, u, t, x0); % lsim generates solution y (=x_1).
plot(y)
C = [ 0 1 0]; % we now pick up y=x_2. Check with soln. in Q1.
sys =ss( A, B, C,0, -1);
y =lsim( sys, u, t ,x0); %Check with soln. in Q1
plot(y)
%
C = [ 0 0 1]; ; %we now pick up x_3 .
sys =ss(A,B,C,0,-1);
y=lsim( sys, u, t ,x0);
plot(y)
C = [1 0 0]; %put C back to what it should be
sys = ss(A, B, C, 0, -1);
y = lsim(sys, u, t, x0);
plot(y) % check to make sure it is what it needs to be.
w =sqrt(Q) * randn(length(t), 1); %process noise
v = sqrt(R) * randn(length(t), 1); %measurement noise
yv = y + v; %noisy output y that the KF needs.
P = B* Q* B'; %initial error covariance
x = zeros(3,1);
ye = zeros( length(t), 1);
ycov = zeros(length(t), 1);

for i = 1 : length(t) %start of the time and measurement updates
Mn = P*C' / (C*P*C' + R);
x = x + Mn*(yv(i) - C*x);
P = (eye(3) - Mn*C)* P;
ye(i) = C*x;
errcov(i) = C*P*C';
x = A*x + B* u(i);
P = A*P*A' + B*Q*B';
end
subplot(211), plot(t,y,'blue', t, ye,'red')
subplot(212), plot(t,y-yv,'blue', t, y-ye,'red')