function cubicRegScript(i,num,rank,k,errTol,maxIts,outputDir) %#codegen
% USAGE: cubicRegScript(i,num,rank,t,R,k,errTol,maxIts,outputDir)
a = (i-1)*num+1;
b = i*num;
m = 9;
n = m;
l = m;
r = rank;
Z = generate_tensor;
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);

% f_phi = @(x) f(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,1);
% grad_phi = @(x) grad(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,2);
% H_phi = @(x) H(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,3);

errFcn = @(x) f(x);

% maxItsALS=30;

for j = a:b
    rng(j+50300000);%each subjob has a unique ID j and is used as seed
    x0 = k * (rand+.5)/2 * randn((m+n+l)*r,1);

    [x,errorHistory] = cubicReg(f,grad,'Hessian',H,'x0',x0,'errFcn',errFcn,'errTol',errTol,'maxIts',maxIts);
    
%     errorHistory = zeros(maxIts+maxItsALS,1);
%     T0={U(x0);V(x0);W(x0)};
%     [T1,~,~,errorHistory(1:maxItsALS)] = cp_als(tensor(Z),r,'maxiters',maxItsALS,'tol',1e-12,'init',T0,'printitn', 0);
%     x1=[T1.U{1}(:);T1.U{2}(:);T1.U{3}(:)];
%     [x,errorHistory(maxItsALS+1:end)] = cubicReg(f,grad,'Hessian',H,'x0',x1,'errFcn',errFcn,'errTol',errTol,'maxIts',maxIts);
    errorHistory(errorHistory==0) = [];
    fprintf("The last entry of errorHistory is %f for index %d, %d/%d.\n",errorHistory(end),j,i,num);
    if errorHistory(end) <= 1e-6
        filename = sprintf("%s/rank%d_k%g_errTol%g_maxIts%g_%d.mat",outputDir,rank,k,errTol,maxIts,j);
        %save data as .mat 
        save(filename,'x0','x','errorHistory');
        figureDir = string(outputDir) + '/figures';
        mkdir(figureDir);
        figurename = sprintf("%s/rank%d_k%g_errTol%g_maxIts%g_%d.png",figureDir,rank,k,errTol,maxIts,j);
        h=figure;
        set(h,'visible','off')
        semilogy(errorHistory);
        xlabel('iterations');
        ylabel('f(x)');
        saveas(h,figurename,'png');
    end
end
end