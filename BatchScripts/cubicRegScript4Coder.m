function cubicRegScript4Coder(i,num,rank,k,errThd,maxIts,outputDir) %#codegen
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
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);

% f_phi = @(x) f(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,1);
% grad_phi = @(x) grad(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,2);
% H_phi = @(x) H(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,3);

errFcn = @(x) f(x);

for j = a:b
    rng(j+3300000);%each subjob has a unique ID j and is used as seed
    x0 = k* randn((m+n+l)*r,1);
    fprintf("The first entry of x0 is %g.\n",x0(1));
    fprintf("%s/rank%d_k%g_errTol%g_maxIts%g.bin\n",outputDir,int8(rank),k,errThd,maxIts);
    [x,errorHistory] = cubicReg4Coder(f,grad,H,x0,errFcn,errThd,maxIts);
    errorHistory(errorHistory==0) = [];
    if errorHistory(end) <= 1e-8
        filename = sprintf("%s/rank%d_k%g_errTol%g_maxIts%g_%d.bin",outputDir,int8(rank),k,errThd,maxIts,int32(j));
        %save data as .mat using parsave
        %save(file,'x0','x','errorHistory');
        fid=fopen(filename,'w');
        fwrite(fid,x0,'double');
        fwrite(fid,x,'double');
        fwrite(fid,errorHistory,'double');
        fclose(fid);
        fprintf("The last entry of errorHistory is %g.\n",errorHistory(end));
%         figureDir = string(outputDir) + '/figures';
%         mkdir(figureDir);
%         figurename = sprintf("%s/rank%d_k%g_errTol%g_maxIts%g_%d.png",figureDir,rank,k,errThd,maxIts,j);
%         h=figure;
%         set(h,'visible','off')
%         semilogy(errorHistory);
%         xlabel('iterations');
%         ylabel('f(x)');
%         saveas(h,figurename,'png');
    end
end
end