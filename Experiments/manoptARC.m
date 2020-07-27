m = 9;
n = 9;
l = 9;
r = 27;
Z = generate_tensor;
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);
Hess = @(x0,x) H(x0)*x;
s = (m+n+l)*r;
% Create the problem structure.
manifold = euclideanfactory(s);
problem.M = manifold;
 
% Define the problem cost function and its Euclidean gradient.
problem.cost  = f;
problem.grad = grad;     % notice the 'e' in 'egrad' for Euclidean
problem.hess = Hess;
 
% Numerically check gradient consistency (optional).
checkgradient(problem);
checkhessian(problem);
% Solve.
[x, xcost, info, options] = arc(problem);
 
% Display some statistics.
figure;
semilogy([info.iter], [info.cost], '.-');
xlabel('Iteration number');
ylabel('Norm of the gradient of f');