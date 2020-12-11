m = 9;
n = 9;
l = 9;
rlist = [27,23,22];
Z = generate_tensor;

opts.MaxIter = 101;
ARCMaxIts = 400;
maxIts = opts.MaxIter + ARCMaxIts;
opts.TolAbs = 1e-12; %fval
errTol = opts.TolAbs; %fval
% opts.TolFun = 1e-30; %relfval
% opts.TolX   = 0; %relstep
N=1000;

for r = rlist

U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);
errFcn = f;

x0 = zeros((m+n+l)*r,N);
x1 = x0;
x = x0;
Out1 = cell(N,1);
Out2 = Out1;
errorHistory = nan(maxIts,N);

for i= 1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    R0={U(x0(:,i));V(x0(:,i));W(x0(:,i))};
    [X,out1] = RARC(Z,R0,opts);
    x1(:,i)=[X{1}(:);X{2}(:);X{3}(:)];
    Out1{i} = out1;
    iter = out1.iterations;
    errorHistory(1:iter,i) = out1.fval;
    if out1.info ~= 1
        [x(:,i),out2] = cubicReg(f,grad,'errTol',errTol,'maxIts',ARCMaxIts,'x0',x1(:,i),'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H);
        errorHistory(iter+1:iter+ARCMaxIts,i) = out2.errHistory(2:end);
        Out2{i} = out2;
    else
        x(:,i) = x1(:,i);
    end
end
fig=figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' SegreARC2ARC'])
xlabel('iterations')
xlim([1 maxIts+1])
ylabel('Objective function value')
ylim([opts.TolAbs/10 1e2])

saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Segre2ARC_' num2str(r) '_fval.fig'])

save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\Segre2ARC_' num2str(r) '.mat'],'x0','x1','x','errorHistory','Out1','Out2');
end
% 
% for r = rlist
% 
% U = @(x) reshape(x(1:m*r),[m,r]);
% V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
% W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
% f = @(x) func_f(Z,x,U,V,W);
% grad = @(x) grad_f(Z,x,U,V,W);
% H = @(x) tensorHessianOptimized(x,U,V,W);
% errFcn = f;
% 
% SegreARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\SegreARC_' num2str(r) '.mat']);
% x0 = SegreARC.x0;
% x1 = SegreARC.x;
% x = zeros(size(x1));
% Out = SegreARC.Out;
% errorHistory = SegreARC.errorHistory;
% 
% for i= 1:N
%     fval = Out{i}.fval(end);
%     iter = Out{i}.iterations;
%     if iter < maxIts && fval > errTol
%         [x(:,i),errorHistory(iter+1:end,i)] = cubicReg(f,grad,'errTol',errTol,'maxIts',maxIts-iter,'x0',x1(:,i),'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H);
%     end
% end
% fig=figure;
% semilogy(errorHistory);
% title(['Rank ' num2str(r) ' SegreARC2ARC'])
% xlabel('iterations')
% xlim([1 maxIts+1])
% ylabel('Objective function value')
% ylim([opts.TolAbs/10 1e2])
% 
% saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Segre2ARC_' num2str(r) '_fval.fig'])
% 
% save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\Segre2ARC_' num2str(r) '.mat'],'x0','x1','x','errorHistory','Out');
% end