m = 9;
n = 9;
l = 9;
rlist = [27,23,22];
Z = generate_tensor;
errTol=1e-12;
maxItsARC=100;
maxItsALS=50;
N=1000;
for r=rlist
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);

errFcn = f;

x0=zeros((m+n+l)*r,N);
x1=x0;
x2=x0;

errorHistory = zeros(maxItsARC+maxItsALS+1,N);
for i=1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    errorHistory(1,i)=f(x0(:,i));
    T0={U(x0(:,i));V(x0(:,i));W(x0(:,i))};
    [T1,~,~,errorHistory(2:maxItsALS+1,i)] = cp_als(tensor(Z),r,'maxiters',maxItsALS,'tol',errTol,'init',T0,'printitn', 0);
    x1(:,i)=[T1.U{1}(:);T1.U{2}(:);T1.U{3}(:)];
    [x2(:,i),errorHistory(maxItsALS+2:end,i)] = cubicReg(f,grad,'errTol',errTol,'maxIts',maxItsARC,'x0',x1(:,i),'errFcn',errFcn,'Hessian',H);
end
fig=figure;
% subplot(3,1,1)
semilogy(errorHistory);
title(['Rank' num2str(r) 'ALS2ARC'])
xlabel('iterations')
xlim([1 size(errorHistory,1)])
ylabel('Objective function value')
ylim([errTol/10 1e2])

saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\ALS2ARC_' num2str(r) '_fval.fig'])
save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ALS2ARC_' num2str(r) '.mat'],'x0','x1','x2','errorHistory');
end
% 
% subplot(3,1,2)
% errorHistory_trunc=errorHistory(51:end,:);
% semilogy(errorHistory_trunc);
% title('ALS2ARC Truncated')
% xlabel('iterations')
% ylabel('total error')
% 
% errorHistory1 = zeros(maxItsARC,N);
% for i=1:N
% [x3(:,i),errorHistory1(:,i)] = cubicReg(f,grad,'errTol',1e-12,'maxIts',maxItsARC,'x0',x0(:,i),'errFcn',errFcn,'Hessian',H);
% %[x(:,i),errorHistory] = cubicReg(f_phi,grad_phi,'errTol',1e-6,'maxIts',2e2,'x0',x0(:,i),'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H_phi);
% end
% 
% subplot(3,1,3)
% semilogy(errorHistory1);
% title('ARC Alone')
% xlabel('iterations')
% ylabel('total error')
% 
% counter=0;
% for i=1:N
%     errHis=errorHistory(:,i);
%     errHis(errHis==0) = [];
%     if errHis(end) < 0.5
%         counter=counter+1;
%     end
% end
% fprintf("In ALSto ARC, %d trials found a solution.\n",counter)
% 
% counter=0;
% for i=1:N
%     errHis=errorHistory1(:,i);
%     errHis(errHis==0) = [];
%     if errHis(end) < 0.5
%         counter=counter+1;
%     end
% end
% fprintf("In ARC alone, %d trials found a solution.\n",counter)

