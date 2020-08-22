m = 9;
n = 9;
l = 9;
rlist = [27,23,22];
Z = generate_tensor;
options.tolcost = 1e-12;
options.tolgradnorm=1e-12;
options.maxiter=100;
options.verbosity=1;
maxiter = options.maxiter;
N=1000;
for r=rlist

%matricize u, v, w
vec = @(x) x(:);
mat = @(x) reshape(x,[m,r*3]);
normalize = @(A) bsxfun(@times, A, 1./sum(A.^2, 1).^.5);
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
Zv=reshape(permute(Z,[3,2,1]),[size(Z,1)^3,1]);
G = @(x) U(x)'*U(x).*(V(x)'*V(x)).*(W(x)'*W(x));
fv = @(x) sum(khatriraoOptimized(khatriraoOptimized(U(x),V(x)),W(x)).*Zv,1).';
lambdav = @(x) G(x)\fv(x);
f = @(x) objFunc4NormalizedTensorCPD(Z,vec(x),U,V,W,lambdav);
egrad = @(x) mat(gradient4NormalizedTensorCPD(Z,vec(x),U,V,W,lambdav));

manifold = obliquefactory(m,r*3);

problem.M = manifold;

% Define the problem cost function and its Euclidean gradient.
problem.cost  = f;
problem.egrad = egrad;     % notice the 'e' in 'egrad' for Euclidean
% problem.ehess = ehess;
 
% Numerically check gradient consistency (optional).
% checkgradient(problem);
% checkhessian(problem);
% Solve.


% [x, xcost, info, ~] = arc(problem,x0,options);
% 
% % Display some statistics.
% figure;
% semilogy([info.iter], [info.cost], '.-');
% xlabel('Iteration number');
% ylabel('Objective function value');


% solThd = 0.5;
x0=zeros((m+n+l)*r,N);
x=zeros(size(x0));
errorHistory = zeros(options.maxiter+1,N);

errFcn = f;

for i=1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
%     X0 = normalize(mat(x0(:,i)));
    X0 = mat(x0(:,i));
    [X, ~, info, ~] = arc(problem,X0,options);
    x(:,i) = vec(X);
    iter=[info.iter];
    cost=[info.cost];
    errorHistory(1:iter(end)+1,i) =  cost.';
end
fig=figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' ManOpt ARC'])
xlabel('iterations')
xlim([1 maxiter+1])
ylabel('Objective function value')
ylim([options.tolcost/10 1e2])

saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\moARC_' num2str(r) '_fval.fig'])
save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\moARC_' num2str(r) '.mat'],'x0','x','errorHistory');
end
