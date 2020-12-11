m = 9;
n = 9;
l = 9;
rlist = [27,23,22];

Z = generate_tensor;
%matricize u, v, w
N=1000;
maxIts=500;
errTol=1e-12;
for r=rlist
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);

errFcn = f;

x0=zeros((m+n+l)*r,N);
x=x0;
errorHistory = zeros(maxIts+1,N);
for i=1:N
x0(:,i) =  0.1*randn((m+n+l)*r,1);
errorHistory(1,i)=f(x0(:,i));
T0={U(x0(:,i));V(x0(:,i));W(x0(:,i))};
[T1,~,~,errorHistory(2:end,i)] = cp_als(tensor(Z),r,'maxiters',maxIts,'tol',errTol,'init',T0,'printitn', 0);
X =  arrayfun(@(k) T1.U{k}*diag(T1.lambda.^(1/3)), 1:length(T1.U), 'UniformOutput', false);
x(:,i)=[X{1}(:);X{2}(:);X{3}(:)];
end
fig=figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' ALS'])
xlabel('iterations')
xlim([1 size(errorHistory,1)])
ylabel('Objective function value')
ylim([errTol/10 1e2])

saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\ALS_' num2str(r) '_fval.fig'])
save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ALS_' num2str(r) '.mat'],'x0','x','errorHistory');
end



h=zeros(3,1);
figure;
for i=1:3
    r=rlist(i);
    ALS=load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ALS_' num2str(r) '.mat'],'x0','x','errorHistory');
    h(i)=subplot(3,1,i);
    semilogy(ALS.errorHistory(:,1:50:end));
    title(['Rank ' num2str(r)])
    xlim([1 size(ALS.errorHistory,1)])
    ylim([1e-1 1e1])
end
xlabel('iterations')

p1=get(h(1),'position');
p2=get(h(2),'position');
p3=get(h(3),'position');
height=(p1(2)+3*p1(4)+p3(2))/2;
h3=axes('position',[p3(1) p3(2) p3(3) height],'visible','off');
h_label=ylabel('objective function value','visible','on');
