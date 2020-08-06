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
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);

errFcn = @(x) f(x);

N=10;
maxItsARC=100;
maxItsNLS=50;
x0=zeros((m+n+l)*r,N);
x1=zeros((m+n+l)*r,N);
x2=zeros(size(x1));
%x3=zeros(size(x1));
errorHistory = zeros(maxItsARC+maxItsNLS,N);
options.Display = false; % Show progress on the command line.
options.Initialization = @cpd_rnd; % Select pseudorandom initialization.
options.Algorithm = @cpd_nls; % Select NLS as the main algorithm.
options.AlgorithmOptions.LineSearch = @cpd_els; % Add exact line search.
options.AlgorithmOptions.TolFun = 1e-12; % Set function tolerance stop criterion
options.AlgorithmOptions.TolX   = 1e-12; % Set step size tolerance stop criterion
options.AlgorithmOptions.MaxIter = maxItsNLS;
options.AlgorithmOptions.CGMaxIter = maxItsNLS*5;
for i=1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    [x1(:,i),errorHistory(1:maxItsARC,i)] = cubicReg(f,grad,'errTol',1e-12,'maxIts',maxItsARC,'x0',x0(:,i),'errFcn',errFcn,'Hessian',H);
    T0={U(x1(:,i));V(x1(:,i));W(x1(:,i))};
    [T1, output] = cpd(Z,T0,options);
    errorHistory(maxItsARC+1:maxItsARC+output.Algorithm.iterations,i) = output.Algorithm.fval(2:end).';
    if output.Algorithm.iterations < maxItsNLS
        errorHistory(maxItsARC+output.Algorithm.iterations+1:end,i) = errorHistory(output.Algorithm.iterations,i) * ones(maxItsNLS-output.Algorithm.iterations,1);
    end
    x2(:,i)=[T1{1}(:);T1{2}(:);T1{3}(:)];
end
figure;
subplot(2,1,1)
semilogy(errorHistory);
title('ARC2tlNLS')
xlabel('iterations')
ylabel('total error')

subplot(2,1,2)
semilogy(errorHistory1);
title('ARC Alone')
xlabel('iterations')
ylabel('total error')

counter=0;
for i=1:N
    errHis=errorHistory(:,i);
    errHis(errHis==0) = [];
    if errHis(end) < 0.5
        counter=counter+1;
    end
end
fprintf("In NLSto ARC, %d triNLS found a solution.\n",counter)

counter=0;
for i=1:N
    errHis=errorHistory1(:,i);
    errHis(errHis==0) = [];
    if errHis(end) < 0.5
        counter=counter+1;
    end
end
fprintf("In ARC alone, %d triNLS found a solution.\n",counter)

save('ARC2tlNLS_23.mat','x0','x1','x2','x3','errorHistory','errorHistory1');
