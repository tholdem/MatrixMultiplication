m = 9;
n = 9;
l = 9;
r = 27;
Z = generate_tensor;

%matricize u, v, w
vec = @(x) x(:);
mat = @(x) reshape(x,[m,r*3]);
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
Zv=reshape(permute(Z,[3,2,1]),[size(Z,1)^3,1]);
G = @(x) U(x)'*U(x).*(V(x)'*V(x)).*(W(x)'*W(x));
fv = @(x) sum(khatriraoOptimized(khatriraoOptimized(U(x),V(x)),W(x)).*Zv,1).';
lambdav = @(x) G(x)\fv(x);
f = @(x) objFunc4NormalizedTensorCPD(Z,vec(x),U,V,W,lambdav);
egrad = @(x) mat(gradient4NormalizedTensorCPD(Z,vec(x),U,V,W,lambdav));
% f = @(x) func_f(Z,vec(x),U,V,W);
% egrad = @(x) mat(grad_f(Z,vec(x),U,V,W));
% H = @(x) tensorHessianOptimized(vec(x),U,V,W);
% ehess = @(x,u) mat(H(x)*vec(u));
% f = @(x) func_f(Z,x,U,V,W);
% egrad = @(x) grad_f(Z,x,U,V,W);
% H = @(x) tensorHessianOptimized(x,U,V,W);
% ehess = @(x,u) H(x)*u;
% Create the problem structure.
manifold = obliquefactory(m,r*3);
% manifold = obliquefactory(m,r*3);

% s = (m+n+l)*r;
% manifold = spherefactory(s);
% manifold = euclideanfactory(s);

problem.M = manifold;

% Define the problem cost function and its Euclidean gradient.
problem.cost  = @(x) f(x);
problem.egrad = egrad;     % notice the 'e' in 'egrad' for Euclidean
% problem.ehess = ehess;
 
% Numerically check gradient consistency (optional).
% checkgradient(problem);
% checkhessian(problem);
% Solve.
normalize = @(A) bsxfun(@times, A, 1./sum(A.^2, 1).^.5);
x0 = normalize(randn(m,3*r));

options.tolgradnorm=1e-12;
options.maxiter=5e2;
[x, xcost, info, ~] = arc(problem,x0,options);

% Display some statistics.
figure;
semilogy([info.iter], [info.cost], '.-');
xlabel('Iteration number');
ylabel('Objective function value');

N=1000;
maxItsARC=100;
maxItsmoARC=50;
solThd = 0.5;
x0=zeros((m+n+l)*r,N);
x1=zeros(size(x0));
x2=zeros(size(x1));
errorHistory = zeros(maxItsARC+maxItsmoARC,N);

options.tolgradnorm=1e-12;
options.maxiter=maxItsmoARC;

errFcn = @(x) f(x);

for i=1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    [x1(:,i), ~, info, ~] = arc(problem,x0(:,i),options);
    iter=[info.iter];
    cost=[info.cost];
    errorHistory(1:iter(end),i) =  cost(2:end).';
    if iter(end) < maxItsmoARC
        errorHistory(iter(end)+1:maxItsmoARC,i) = errorHistory(iter(end),i) * ones(maxItsmoARC-iter(end),1);
    end
    [x2(:,i),errorHistory(maxItsmoARC+1:end,i)] = cubicReg(f,egrad,'errTol',1e-12,'maxIts',maxItsARC,'x0',x1(:,i),'errFcn',errFcn,'Hessian',H);
end
figure;
subplot(3,1,1)
semilogy(errorHistory);
title('tlmoARC2ARC')
xlabel('iterations')
ylabel('total error')

subplot(3,1,2)
errorHistory_trunc=errorHistory(maxItsmoARC+1:end,:);
semilogy(errorHistory_trunc);
title('tlmoARC2ARC Truncated')
xlabel('iterations')
ylabel('total error')

% errorHistory1 = zeros(maxItsARC,N);
% for i=1:N
% [x3(:,i),errorHistory1(:,i)] = cubicReg(f,grad,'errTol',1e-12,'maxIts',maxItsARC,'x0',x0(:,i),'errFcn',errFcn,'Hessian',H);
% end

subplot(3,1,3)
semilogy(errorHistory1);
title('ARC Alone')
xlabel('iterations')
ylabel('total error')

counter=0;
for i=1:N
    errHis=errorHistory(:,i);
    errHis(errHis==0) = [];
    if errHis(end) < solThd
        counter=counter+1;
    end
end
fprintf("In moARCto ARC, %d trials found a solution.\n",counter)

counter=0;
for i=1:N
    errHis=errorHistory1(:,i);
    errHis(errHis==0) = [];
    if errHis(end) < solThd
        counter=counter+1;
    end
end
fprintf("In ARC alone, %d trials found a solution.\n",counter)

save('moARC2ARC_23.mat','x0','x1','x2','x3','errorHistory','errorHistory1');
