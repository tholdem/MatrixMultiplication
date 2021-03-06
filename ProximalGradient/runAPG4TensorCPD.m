m = 9;
n = 9;
l = 9;
r = 23;
Z = generate_tensor;
Zv=reshape(permute(Z,[3,2,1]),[size(Z,1)^3,1]);
vec = @(A) A(:);
%matricize u, v, w
% N = @(A) diag(1./sum(A.^2,1).^0.5);
normalize = @(x) [vec(U(x)./sum(U(x).^2,1).^0.5);vec(V(x)./sum(V(x).^2,1).^0.5);vec(W(x)./sum(W(x).^2,1).^0.5)];

U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
% Un = @(x) normalize(U(x));
% Vn = @(x) normalize(V(x));
% Wn = @(x) normalize(W(x));
G = @(x) U(x)'*U(x).*(V(x)'*V(x)).*(W(x)'*W(x));
fv = @(x) sum(khatriraoOptimized(khatriraoOptimized(U(x),V(x)),W(x)).*Zv,1).';
lambdav = @(x) G(x)\fv(x);
Upsilon = @(x) objFunc4NormalizedTensorCPD(Z,x,U,V,W,lambdav);
gradUpsilon = @(x) gradient4NormalizedTensorCPD(Z,x,U,V,W,lambdav);

gamma = 0.5;%TODO
eta = 0.0000001;
p=10;
mu = @(A) sum(triu((A.'*A).^(2*p),1),'all')^(1/(2*p));
Omega = @(A) (A.'*A).^(2*p-2);
C = @(x) 1-r+1/(mu(U(x))*mu(V(x))*mu(W(x)));
L = @(A,B,C) -1/(sum(triu((A.'*A).^(2*p),1),'all')^(1/(2*p)+1)*mu(B)*mu(C));
gradC = @(x) [vec(L(U(x),V(x),W(x)) * U(x) * (U(x).'*U(x) .* (Omega(U(x)).*~eye(r,r)))); ...
    vec(L(V(x),U(x),W(x)) * V(x) * (V(x).'*V(x) .* (Omega(V(x)).*~eye(r,r)))); ...
    vec(L(W(x),V(x),U(x)) * W(x) * (W(x).'*W(x) .* (Omega(W(x)).*~eye(r,r))))];

%input must have unit-norm columns
coherence = @(x) eta * exp(-gamma*C(x));
gradCoherence= @(x) -eta*gamma/exp(gamma*C(x)) * gradC(x);

f = Upsilon;
grad = gradUpsilon;
R=coherence;
gradR=gradCoherence;

errFcn = @(x) f(x)+R(x);
x0 =  normalize(randn((m+n+l)*r,1));

[x,errorHistory] = APG4TensorCPD(f,grad,R,gradR,'errTol',1e-6,'maxIts',1e3,'x0',x0,'errFcn',errFcn,'U',U,'V',V,'W',W);
semilogy(errorHistory);
xlabel('iterations')
ylabel('total error')