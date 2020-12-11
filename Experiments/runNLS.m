m = 9;
n = 9;
l = 9;
rlist = [27,23,22];

Z = fmt(generate_tensor);

options.Display = false; % Show progress on the command line.
options.Initialization = @cpd_rnd; % Select pseudorandom initialization.
options.Algorithm = @cpd_nls; % Select NLS as the main algorithm.
options.AlgorithmOptions.LineSearch = @cpd_els; % Add exact line search.
options.AlgorithmOptions.TolFun = 1e-12; % Set function tolerance stop criterion
options.AlgorithmOptions.TolX   = -1; % Set step size tolerance stop criterion
options.AlgorithmOptions.MaxIter = 500;
options.AlgorithmOptions.CGMaxIter = 500;

N=1000;
maxIts = options.AlgorithmOptions.MaxIter;
errTol = options.AlgorithmOptions.TolFun;
for r=rlist
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);


x0=zeros((m+n+l)*r,N);
x=x0;
errorHistory = nan(maxIts+1,N);
Out = cell(N,1);
for i=1:N
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    T0={U(x0(:,i));V(x0(:,i));W(x0(:,i))};
    [T, output] = cpd(Z,T0,options);
    errorHistory(1:output.Algorithm.iterations+1,i) =  output.Algorithm.fval.';
    x(:,i)=[T{1}(:);T{2}(:);T{3}(:)];
    Out{i}=output;
end
fig=figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' NLS'])
xlabel('iterations')
xlim([1 size(errorHistory,1)])
ylabel('Objective function value')
ylim([errTol/10 1e2])

saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\NLS_' num2str(r) '_fval.fig'])
save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\NLS_' num2str(r) '.mat'],'x0','x','errorHistory','Out');
end