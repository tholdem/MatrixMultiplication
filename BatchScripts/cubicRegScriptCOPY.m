function cubicRegScriptCOPY(i,num,rank,t,R,k,errThd,maxIts) %#codegen
% USAGE: cubicRegScript(i,num,rank,t,R,k,errThd,maxIts,outputDir)
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
f=@(x) norm(U(x)*V(x).');
grad = @(x) eig(x*x.');
H = @(x) tensorHessianOptimized(x,U,V,W);

f_phi = @(x) f(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,1);
grad_phi = @(x) grad(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,2);
H_phi = @(x) H(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,3);

errFcn = @(x) f(x);

for j = a:b
    rng(j);%each subjob has a unique ID j and is used as seed
    x0 = k* randn((m+n+l)*r,1);
    [x,errorHistory] = cubicRegCOPY(f_phi,grad_phi,H_phi,x0,errThd,maxIts,errFcn);
    errorHistory(errorHistory==0) = [];
    fprintf("The last entry of errorHistory is %f.\n",errorHistory(end));
end
end