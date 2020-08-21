m = 9;
n = 9;
l = 9;
r = 23;
Z = generate_tensor;

manifold = cell(r,1);
fieldnames = cell(r,1);
intarray = [1:r];
for i=1:r
    fieldnames{i}=['f' int2str(intarray(i))];
end
manifold(1:r) = {fixedranktensorembeddedfactory(m*ones(1,3),ones(1,3))};
problem.M = productmanifold(cell2struct(manifold,fieldnames));

f = @(P) productSegreManifoldObjFcn(Z,P,fieldnames);
egrad = @(P) productSegreManifoldGrad(Z,P,fieldnames);

U = {rand(9,27), rand(9,27), rand(9,27)}; %<-- The matrices.
X = ttensor(core,U);
Y=full(X);
Y1 = full(ktensor(U));

vec=@(x) x(:);
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
ttensor2vec = @(T) [vec(T.X.U{1});vec(T.X.U{2});vec(T.X.U{3})];
f = @(x) func_f(Z,ttensor2vec(x),U,V,W);
H = @(x) tensorHessianOptimized(vec(x),U,V,W);

% vec = @(X) X(:);
% f = @(x) func_f(Z,vec(x),U,V,W);
% egrad = @(x) mat(grad_f(Z,vec(x),U,V,W));
% H = @(x) tensorHessianOptimized(vec(x),U,V,W);
% ehess = @(x,u) mat(H(x)*vec(u));
% f = @(x) func_f(Z,x,U,V,W);
% egrad = @(x) grad_f(Z,x,U,V,W);
% H = @(x) tensorHessianOptimized(x,U,V,W);
% ehess = @(x,u) H(x)*u;
% s = (m+n+l)*r;
% Create the problem structure.

% Define the problem cost function and its Euclidean gradient.
problem.cost  = f;
problem.egrad = egrad;     % notice the 'e' in 'egrad' for Euclidean
% problem.ehess = ehess;

% Numerically check gradient consistency (optional).
checkgradient(problem);
% checkhessian(problem);
% Solve.
options.tolgradnorm=1e-2;
options.maxiter=1e1;
tic;
[x, xcost, info, options] = arc(problem,[],options);
toc;
% Display some statistics.
figure;
semilogy([info.iter], [info.cost], '.-');
xlabel('Iteration number');
ylabel('Objective function value');