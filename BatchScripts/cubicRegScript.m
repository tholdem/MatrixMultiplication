function cubicRegScript(i,rank,t,R,k,errThd,maxIts,output_dir)
% USAGE: cubicRegScript(i,rank,errThd,maxIts,output_dir)
rng(i);
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
H = @(x) tensorHessian(Z,x,U,V,W);

f_phi = @(x) f(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,1);
grad_phi = @(x) grad(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,2);
H_phi = @(x) H(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,3);

errFcn = @(x) f(x);
x0 = k* randn((m+n+l)*r,1);

try
    [x,errorHistory] = cubicReg(f_phi,grad_phi,'errThd',errThd,'maxIts',maxIts,'x0',x0,'errFcn',errFcn,'iterInterval',100,'method','adaptive','Hessian',H_phi,'projection','off','penalty','on');
catch ME
    disp('Error Message:')
    disp(ME.message)
    fprintf('The script terminated prematurely. Setting outputs to zero.\n')
    x = 0;
    errorHistory = 0;
end
errorHistory(errorHistory==0) = [];
if errorHistory(end) <= 
filename = string(output_dir) + '/rank' + string(rank) + '_error' + string(errThd) + '_' + string(i);
%save data as .mat
save(filename,'x0','x','errorHistory');