function [x,errHistory] = cubicRegCOPY(f,grad,H,x,errThd,maxIts,errFcn) %#codegen
%Usage: [x,errFcn] = cubicReg(f,grad,varargin)
%most code is adapted from this python implementation
%https://github.com/cjones6/cubic_reg/blob/2d1ed4c156bdfc34159b374a264012f3fe79adfe/src/cubic_reg.py#L258
%citations include:
%C. Cartis, N. I. M. Gould, and P. L. Toint, “Adaptive cubic regularisation methods for unconstrained optimization. Part I: Motivation, convergence and numerical results,” Math. Program., vol. 127, no. 2, pp. 245–295, 2011.
%Conn, A. R., Gould, N. I., & Toint, P. L. (2000). Trust region methods (Vol. 1). Siam.

sigma=1;
eta1=0.1;
eta2=0.9;
kappa_easy=0.001;

errHistory = zeros(maxIts,1);
% if p.Results.projection == "on"
%     Proj = p.Results.projFcn;
% else
%     Proj = @(x) x;
% end
% if p.Results.penalty == "on"
% else
% end

%m = @(p,fx,gx,Hx,sigma) fx+ dot(p,gx) + 0.5 * dot(Hx*p,p) + 1/3*sigma*norm(p)^3;
%we can remove fx since we are using the difference between fx and m(p)
m = @(p,gx,Hx,sigma) dot(p,gx) + 0.5 * dot(Hx*p,p) + 1/3*sigma*norm(p)^3;

fx = f(x);
gx = grad(x);
Hx = H(x);
[V,D] = eig(Hx);
v1 = V(:,1);
lambda1 = D(1,1);
%Hess = Hess(x,p);%in case explicit Hessian is not available
i=0;
%Cartis et al 2011 Algorithm 2.1 
while norm(gx) > errThd && i < maxIts
    i=i+1;
    p = ARCSubproblem(gx,Hx,v1,lambda1,sigma,kappa_easy,maxIts/10);
    rho  = (fx-f(x+p))/(-m(p,gx,Hx,sigma));
    %successful, move in that direction
    if rho >= eta1
        %x = Proj(x + p);
        x = x + real(p);
        %fprintf('norm(x)=%f\n',norm(x))
        fx = f(x);
        gx = grad(x);
        Hx = H(x);
        [V,D] = eig(Hx);
        v1 = V(:,1);
        lambda1 = D(1,1);
        %Hess = Hess(x,p);
        %very successful,expand TR radius
        if rho > eta2
           sigma = 0.5 * sigma;
        end
    %unsuccessful, shrink TR radius
    else
        sigma = 2 * sigma;
    end
    errHistory(i)     = real(errFcn(x));
%         if ~mod( i, iterInterval )
%             fprintf('Iteration %5d, error is %.2e\n', i, errHistory(i) );
%         end
end
%fprintf("sigma=%f\n",sigma);

end