%{
This is an example using a correct gradient to see what
the output of gradientCheck.m should look like

-Stephen
%}

rng(0);
%n   = 10; % be careful: if n is large, default behavior changes
 n   = 100;
A   = randn(n);
b   = randn(n,1);
f   = @(x) norm( A*x - b )^2/2;
%gra = @(x) A'*(A*x-b);
 gra = @(x) A'*(A*x-b); % wrong gradient

x0  = randn(n,1);


gradientCheck( f, gra, x0 ); % defaults
%%

scaling = 1e0;
numberPoints = 5;
gradientCheck( f, gra, x0 )

%% if n is large, it won't do "forward diff" and "central diff" by default
% (since these form the entire n-dimensional gradient)
% so if you want these, turn "FORCE_FINITE_DIFF" to true

scaling = 1e-3
numberPoints    = 20;
FORCE_FINITE_DIFF = true;
gradientCheck( f, gra, x0, scaling, numberPoints, FORCE_FINITE_DIFF );

%% 2020
%{
Todo:
  For large dimensions, when finding the entire forward/centra diff
gradient is slow, use a randomized estimator (along SSD lines)

%}

%% evalPenaltyFcn

t = 0.1;
R = 1;

m = randi(20);
n = randi(20);
r = min(m,n);
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:end),[n,r]);
f = @(x) evalPenaltyFcn(x,t,R,U,V,1);
grad = @(x) evalPenaltyFcn(x,t,R,U,V,2);


x0 = randn(r*(m+n),1);
gradientCheck( f, grad, x0,1,10,true);

%% CP factorization
m = 9;
n = 9;
l = 9;
r = 23;
Z = generate_tensor;
vec = @(A) A(:);
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) fUc_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessian(Z,x,U,V,W);
hess = @(x0,x) H(x0)*x;
x0 = randn((m+n+l)*r,1);


gradientCheck( f, grad, x0,1,10,true);

%% Scaled CP factorization
m = 9;
n = 9;
l = 9;
r = 23;
Z = generate_tensor;
Zv=reshape(permute(Z,[3,2,1]),[size(Z,1)^3,1]);
vec = @(A) A(:);
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);

G = @(x) U(x)'*U(x).*(V(x)'*V(x)).*(W(x)'*W(x));
fv = @(x) sum(khatriraoOptimized(khatriraoOptimized(U(x),V(x)),W(x)).*Zv,1).';
lambdav = @(x) G(x)\fv(x);
f = @(x) objFUc4NormalizedTensorCPD(Z,x,U,V,W,lambdav);
grad = @(x) gradient4NormalizedTensorCPD(Z,x,U,V,W,lambdav);

t=1;
coherence = @(x) -1/t * log(C(x));
gradCoherence= @(x) -1/(t*C(x)) * gradC(x);
p=10;
mu = @(A) sum(triu((A.'*A).^(2*p),1),'all')^(1/(2*p));
Omega = @(A) (A.'*A).^(2*p-2);
C = @(x) 1-r+1/(mu(U(x))*mu(V(x))*mu(W(x)));
L = @(A,B,C) -1/(sum(triu((A.'*A).^(2*p),1),'all')^(1/(2*p)+1)*mu(B)*mu(C));
gradC = @(x) [vec(L(U(x),V(x),W(x)) * U(x) * (U(x).'*U(x) .* (Omega(U(x)).*~eye(r,r)))); ...
    vec(L(V(x),U(x),W(x)) * V(x) * (V(x).'*V(x) .* (Omega(V(x)).*~eye(r,r)))); ...
    vec(L(W(x),V(x),U(x)) * W(x) * (W(x).'*W(x) .* (Omega(W(x)).*~eye(r,r))))];

x0 = randn((m+n+l)*r,1);
gradientCheck( f, grad, x0,1,10,true);
gradientCheck( C, gradC, x0,1,10,true);
gradientCheck( coherence, gradCoherence, x0,1,10,true);


s = (m+n+l)*r;
% Create the problem structure.
manifold = euclideanfactory(s);
problem.M = manifold;
 
% Define the problem cost fUction and its Euclidean gradient.
problem.cost  = f;
problem.grad = grad;
problem.cost  = coherence;
problem.grad = gradCoherence;

checkgradient(problem);
