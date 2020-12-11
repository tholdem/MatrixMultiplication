m = 9;
n = 9;
l = 9;
rlist = [27,23,22];
Z = generate_tensor;

opts.MaxIter = 101;
maxItsARC=opts.MaxIter;
maxItsALS=50;
opts.TolAbs = 1e-12; %fval
opts.TolFun = 1e-30; %relfval
opts.TolX   = 1e-12; %relstep
N=10;

for r = rlist

U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);

x0 = zeros((m+n+l)*r,N);
x1=x0;
x2=x0;
errorHistory = zeros(maxItsARC+maxItsALS,N);
Out = cell(N,1);

for i= 1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    errorHistory(1,i)=f(x0(:,i));
    T0={U(x0(:,i));V(x0(:,i));W(x0(:,i))};
    [T1,~,~,errorHistory(2:maxItsALS+1,i)] = cp_als(tensor(Z),r,'maxiters',maxItsALS,'tol',opts.TolAbs,'init',T0,'printitn', 0);
%     R0 =  arrayfun(@(k) T1.U{k}*diag(T1.lambda.^(1/3)), 1:length(T1.U), 'UniformOutput', false);
    x1(:,i)=[T1.U{1}(:);T1.U{2}(:);T1.U{3}(:)];
    [X,out] = RARC_HR(Z,T1.U,opts);
    x2(:,i)=[X{1}(:);X{2}(:);X{3}(:)];
    Out{i} = out;
    errorHistory(maxItsALS+2:maxItsALS+out.iterations,i) = out.fval(2:end);
end
fig=figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' Segre Manifold Product ARC with Hot Restart'])
xlabel('iterations')
xlim([1 size(errorHistory,1)])
ylabel('Objective function value')
ylim([opts.TolAbs/10 1e2])

saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\ALS2SegreARC_' num2str(r) '_fval.fig'])
save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ALS2SegreARC_' num2str(r) '.mat'],'x0','x1','x2','errorHistory','Out');
end