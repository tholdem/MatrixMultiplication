m = 9;
n = 9;
l = 9;
r = 22;
Z = generate_tensor;
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);

errFcn = @(x) f(x);

N=1000;
maxItsARC=100;
maxItsALS=50;
x0=zeros((m+n+l)*r,N);
x1=zeros((m+n+l)*r,N);
x2=zeros(size(x1));
x3=zeros(size(x1));
errorHistory = zeros(maxItsARC+maxItsALS,N);
for i=1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    T0={U(x0(:,i));V(x0(:,i));W(x0(:,i))};
    [T1,~,~,errorHistory(1:maxItsALS,i)] = cp_als(tensor(Z),r,'maxiters',maxItsALS,'tol',1e-12,'init',T0,'printitn', 0);
    x1(:,i)=[T1.U{1}(:);T1.U{2}(:);T1.U{3}(:)];
    [x2(:,i),errorHistory(maxItsALS+1:end,i)] = cubicReg(f,grad,'errTol',1e-12,'maxIts',maxItsARC,'x0',x1(:,i),'errFcn',errFcn,'Hessian',H);
    %[x(:,i),errorHistory] = cubicReg(f_phi,grad_phi,'errTol',1e-6,'maxIts',2e2,'x0',x0(:,i),'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H_phi);
end
figure;
subplot(3,1,1)
semilogy(errorHistory);
title('ALS2ARC')
xlabel('iterations')
ylabel('total error')

subplot(3,1,2)
errorHistory_trunc=errorHistory(51:end,:);
semilogy(errorHistory_trunc);
title('ALS2ARC Truncated')
xlabel('iterations')
ylabel('total error')

errorHistory1 = zeros(maxItsARC,N);
for i=1:N
[x3(:,i),errorHistory1(:,i)] = cubicReg(f,grad,'errTol',1e-12,'maxIts',maxItsARC,'x0',x0(:,i),'errFcn',errFcn,'Hessian',H);
%[x(:,i),errorHistory] = cubicReg(f_phi,grad_phi,'errTol',1e-6,'maxIts',2e2,'x0',x0(:,i),'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H_phi);
end

subplot(3,1,3)
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
fprintf("In ALSto ARC, %d trials found a solution.\n",counter)

counter=0;
for i=1:N
    errHis=errorHistory1(:,i);
    errHis(errHis==0) = [];
    if errHis(end) < 0.5
        counter=counter+1;
    end
end
fprintf("In ARC alone, %d trials found a solution.\n",counter)

save('ALS2ARC_22.mat','x0','x1','x2','x3','errorHistory','errorHistory1');
