m = 9;
n = 9;
l = 9;
r = 23;
Z = generate_tensor;
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
egrad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);
ehess = @(x,u) H(x)*u;
s = (m+n+l)*r;
% Create the problem structure.
manifold = spherefactory(s);
problem.M = manifold;

% Define the problem cost function and its Euclidean gradient.
problem.cost  = f;
problem.grad = @(x) manifold.egrad2rgrad(x, egrad(x));     % notice the 'e' in 'egrad' for Euclidean
problem.hess = @(x, u) manifold.ehess2rhess(x, egrad(x), ehess(x,u), u);
 
% Numerically check gradient consistency (optional).
% checkgradient(problem);
% checkhessian(problem);
% Solve.
[x, xcost, info, options] = trustregions(problem);
 
% Display some statistics.
figure;
semilogy([info.iter], [info.cost], '.-');
xlabel('Iteration number');
ylabel('Objective function value');