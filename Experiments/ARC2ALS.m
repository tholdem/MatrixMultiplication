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

N=1000;
maxIts1=100;
maxIts2=100;
x0=zeros((m+n+l)*r,N);
x1=zeros(size(x0));
x2=zeros(size(x0));
errorHistory = zeros(maxIts1+maxIts2,N);
for i=1:N
x0(:,i) =  0.1*randn((m+n+l)*r,1);
%%
[x1(:,i),errorHistory(1:maxIts1,i)] = cubicReg(f,grad,'errTol',1e-12,'maxIts',maxIts1,'x0',x0(:,i),'errFcn',errFcn,'Hessian',H);
%[x(:,i),errorHistory] = cubicReg(f_phi,grad_phi,'errTol',1e-6,'maxIts',2e2,'x0',x0(:,i),'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H_phi);
T0={U(x1(:,i));V(x1(:,i));W(x1(:,i))};
[T1,~,~,errorHistory(maxIts1+1:end,i)] = cp_als(tensor(Z),r,'maxiters',maxIts2,'tol',1e-12,'init',T0,'printitn', 0);
x2(:,i)=[T1.U{1}(:);T1.U{2}(:);T1.U{3}(:)];
end
figure;
semilogy(errorHistory);
xlabel('iterations')
ylabel('total error')

