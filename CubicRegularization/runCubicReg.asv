m = randi(100);
n = randi(100);
%r=randi(min(m,n));
r = min(m,n);
N = r*(m+n);
A = randn(m,r)*randn(r,n);
[U,~,V] = svd(A);
%projection matrices to column spaces of true U and V
P = U/(U.'*U)*U.';
Q = V/(V.'*V)*V.';

vec = @(x) x(:);
%matricize u and v
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:end),[n,r]);
g = @(x) U(x)*V(x).'-A ;
f = @(x) 1/N*norm(g(x),'Fro')^2;
gradient = @(x) [vec(g(x)*V(x));vec(g(x).'*U(x))];
hessian = @(x) 
%see difference between computed U.V and their projections to true U,V's
%column spaces
errFcn = @(x) norm(U(x)-P*U(x))+norm(V(x)-Q*V(x));
x = randn(r*(m+n),1);
%scale since it works much better
%x = x/norm(A,'Fro');
norm(U(x)*V(x).','Fro')
%need to adjust scaling factor for large matrices (n>50)
gradientCheck( f, gradient, x,1e-3);

[x,errorHistory] = gradientDescent(f,gradient,'errorThd',1e-6,'maxIts',1e5,'initialPoint',x,'algo',2,'matrix',A,'rank',r,'errFcn',errFcn,'iterInterval',20);
U = U(x);
V = V(x);
semilogy(errorHistory);
xlabel('iterations')
ylabel('total error')

