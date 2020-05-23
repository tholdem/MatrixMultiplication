% r=randi(50);
% A=randn(r,randi(r));
% b=randn(size(A,1),1);
% f   = @(x) norm( A*x - b )^2/2;
% grad = @(x) A'*(A*x-b);
% hess = @(x,x0) A'*A*x;
% x0 = randn(size(A,2),1);

m = randi(10);
n = randi(10);
%r=randi(min(m,n));
r = min(m,n);
A = randn(m,r)*randn(r,n);

vec = @(x) x(:);
%matricize u and v
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:end),[n,r]);
g = @(x) U(x)*V(x).'-A ;
f = @(x) .5*norm(g(x),'Fro')^2;
grad = @(x) [vec(g(x)*V(x));vec(g(x).'*U(x))];
%this is the function after H(x0) is applied to x, i.e. hess(x,x0) = H(x0)*x
hess = @(x,x0) [vec(U(x)*V(x0)'*V(x0))+vec(U(x0)*V(x)'*V(x0)+g(x0)*V(x));vec((U(x)*V(x0)')'*U(x0)+g(x0)'*U(x))+vec((U(x0)*V(x)')'*U(x0))];
x0 = randn(r*(m+n),1);

HessianCheck(f,grad,hess,x0);