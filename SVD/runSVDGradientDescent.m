m = randi(100);
n = randi(100);
%r=randi(min(m,n));
r = min(m,n);

A = randn(m,r)*randn(r,n);
vec = @(x) x(:);
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:end),[n,r]);
g = @(x) U(x)*V(x).'-A ;
f = @(x) .5*norm(g(x),'Fro')^2;
gradient = @(x) [vec(g(x)*V(x));vec(g(x).'*U(x))];

x = randn(r*(m+n),1);

[x,errorHistory] = gradientDescent(f,gradient,'errorThd',1e-6,'maxIts',1e5,'initialPoint',x,'algo',2,'matrix',A,'rank',r,'iterInterval',20);
U = U(x);
V = V(x);
semilogy(errorHistory);
xlabel('iterations')
ylabel('total error')