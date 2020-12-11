m = 9;
n = 9;
l = 9;
rlist = [27,23,22];
Z = generate_tensor;

maxIts = 501;
opts.TolAbs = 1e-12;
opts.TolX = 1e-12;
errTol = opts.TolAbs; %fval
% opts.TolFun = 1e-30; %relfval
% opts.TolX   = 0; %relstep
N=1000;

for r = rlist

U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);


ARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat']);
x0 = ARC.x0;
x1 = ARC.x;
x = zeros(size(x1));
Out = cell(N,1);
errorHistory = ARC.errorHistory;

for i= 1:N
    errH = errorHistory(:,i);
    last = errH(end);
    errH(errH==last) = [];
    if last == 0
        fval = errH(end);
    else
        fval = last;
    end
    iter = size(errH,1);
    if iter < maxIts-1 && fval > errTol
        opts.MaxIter = maxIts-iter;
        R0={U(x1(:,i));V(x1(:,i));W(x1(:,i))};
        [X,out] = RARC(Z,R0,opts);
        x(:,i)=[X{1}(:);X{2}(:);X{3}(:)];
        Out{i} = out;
        errorHistory(iter+1:iter+out.iterations,i) = out.fval;
    end
end
fig=figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' ARC2SegreARC'])
xlabel('iterations')
xlim([1 maxIts+1])
ylabel('Objective function value')
ylim([opts.TolAbs/10 1e2])

% saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\ARC2Segre_' num2str(r) '_fval.fig'])
% saveas(png,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\ARC2Segre_' num2str(r) '_fval.png'])
% 
% save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC2Segre_' num2str(r) '.mat'],'x0','x1','x','errorHistory','Out');
end