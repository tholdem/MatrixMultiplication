m = 9;
n = 9;
l = 9;
rlist = [27,23,22];
Z = generate_tensor;

opts.MaxIter = 100;
MaxIter = opts.MaxIter;
opts.TolAbs = 1e-10; %fval
opts.TolFun = 1e-30; %relfval
opts.TolX   = 1e-10; %relstep

for j=1:3
r = rlist(j);
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);

N=500;
x0 = zeros((m+n+l)*r,N);
x = x0;
Out = cell(N,1);
errorHistory = zeros(MaxIter+1,N);
for i= 1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    R0={U(x0(:,i));V(x0(:,i));W(x0(:,i))};
    [X,out] = RARC_HR(Z,R0,opts);
    x(:,i)=[X{1}(:);X{2}(:);X{3}(:)];
    Out{i} = out;
    errorHistory(1:out.iterations,i) = out.fval;
end
figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' Segre Manifold Product ARC with Hot Restart'])
xlabel('iterations')
xlim([1 MaxIter+1])
ylabel('Objective function value')

save(['SegreARC_' num2str(r) '.mat'],'x0','x','errorHistory','Out');
end