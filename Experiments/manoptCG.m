m = 9;
n = 9;
l = 9;
r = 22;
Z = generate_tensor;
Zv=reshape(permute(Z,[3,2,1]),[size(Z,1)^3,1]);

%matricize u, v, w
vec = @(X) X(:);
mat = @(x) reshape(x,[m,r*3]);
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
G = @(x) U(x)'*U(x).*(V(x)'*V(x)).*(W(x)'*W(x));
fv = @(x) sum(khatriraoOptimized(khatriraoOptimized(U(x),V(x)),W(x)).*Zv,1).';
lambdav = @(x) G(x)\fv(x);
f = @(x) objFunc4NormalizedTensorCPD(Z,vec(x),U,V,W,lambdav);
egrad = @(x) mat(gradient4NormalizedTensorCPD(Z,vec(x),U,V,W,lambdav));

% Create the problem structure.
manifold = obliquefactory(m,r*3);
problem.M = manifold;

% Define the problem cost function and its Euclidean gradient.
problem.cost  = f;
problem.egrad = egrad;     % notice the 'e' in 'egrad' for Euclidean
 
% Numerically check gradient consistency (optional).
% checkgradient(problem);

%X0 = randn(m,3*r);
options.tolgradnorm=1e-8;
options.maxiter=1e3;
% Solve.
N=10;
for i=1:N
[x, xcost, info, options] = conjugategradient(problem,x0,options);
% Display some statistics.
figure;
semilogy([info.iter], [info.cost], '.-');
xlabel('Iteration number');
ylabel('Objective function value');
end