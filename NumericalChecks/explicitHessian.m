
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

%Hessuu = @(x0,x) vec(U(x)*V(x0)'*V(x0));
Huu = @(x0) kron(V(x0)'*V(x0),eye(m));

%Hessuv = @(x0,x) vec(U(x0)*V(x)'*V(x0)+g(x0)*V(x));
Huv = @(x0) kron(V(x0)',U(x0))*boxProduct(eye(n),eye(r)) +kron(eye(r),g(x0));

%Hessvu = @(x0,x) vec((U(x)*V(x0)')'*U(x0)+g(x0)'*U(x));
Hvu = @(x0) kron(U(x0)',V(x0))*boxProduct(eye(m),eye(r))+kron(eye(r),g(x0)');

%Hessvv = @(x0,x) vec((U(x0)*V(x)')'*U(x0));
Hvv = @(x0) kron(U(x0)'*U(x0),eye(n));

H = @(x0) [Huu(x0) Huv(x0);Hvu(x0) Hvv(x0)];

x0 = randn(r*(m+n),1);
x = randn(r*(m+n),1);

% norm(Huu(x0)*vec(U(x)) - Hessuu(x0,x))
% norm(Huv(x0)*vec(V(x)) - Hessuv(x0,x))
% norm(Hvu(x0)*vec(U(x)) - Hessvu(x0,x))
% norm(Hvv(x0)*vec(V(x)) - Hessvv(x0,x))

% hess = @(x0,x) [vec(U(x)*V(x0)'*V(x0))+vec(U(x0)*V(x)'*V(x0)+g(x0)*V(x));vec((U(x)*V(x0)')'*U(x0)+g(x0)'*U(x))+vec((U(x0)*V(x)')'*U(x0))];
% dot(x,H(x0)*x)-dot(x,hess(x0,x))