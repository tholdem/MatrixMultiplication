function [x,errHistory] = cubicReg(f,grad,varargin) %#codegen
%Usage: [x,errFcn] = cubicReg(f,grad,varargin)
%most code is adapted from this python implementation
%https://github.com/cjones6/cubic_reg/blob/2d1ed4c156bdfc34159b374a264012f3fe79adfe/src/cubic_reg.py#L258
%citations include:
%C. Cartis, N. I. M. Gould, and P. L. Toint, “Adaptive cubic regularisation methods for unconstrained optimization. Part I: Motivation, convergence and numerical results,” Math. Program., vol. 127, no. 2, pp. 245–295, 2011.
%Conn, A. R., Gould, N. I., & Toint, P. L. (2000). Trust region methods (Vol. 1). Siam.
p = inputParser;
addParameter(p,'errTol',1e-6,@(x) x>0);
addParameter(p,'x0',0);
addParameter(p,'sigma0',1);
addParameter(p,'sigma_min',1e-2);
addParameter(p,'eta1',0.1);
addParameter(p,'eta2',0.9);
addParameter(p,'kappa_easy',1e-3);
%exact explicit hessian
addParameter(p,'Hessian',0);
%exact implicit Hessian to save computation
%addParameter(p,'implicitHessian',0);
addParameter(p,'maxIts',1e5,@(x) x>0);
addParameter(p,'errFcn',0);

parse(p,varargin{:});

errTol = p.Results.errTol;
x = p.Results.x0;
H = p.Results.Hessian;
%Hess = p.Results.implicitHessian;
maxIts  = p.Results.maxIts;
errFcn = p.Results.errFcn;

errHistory = zeros(maxIts,1);

%m = @(p,fx,gx,Hx,sigma) fx+ dot(p,gx) + 0.5 * dot(Hx*p,p) + 1/3*sigma*norm(p)^3;
%we can remove fx since we are using the difference between fx and m(p)
m = @(p,gx,Hx,sigma) dot(p,gx) + 0.5 * dot(Hx*p,p) + 1/3*sigma*norm(p)^3;

sigma = p.Results.sigma0;
sigma_min = p.Results.sigma_min;
eta1 = p.Results.eta1;
eta2 = p.Results.eta2;
kappa_easy = p.Results.kappa_easy;

fx = f(x);
gx = grad(x);
Hx = H(x);
[V,D]=eig(Hx);
v1 = V(:,1);
lambda1 = D(1,1);
% %tried eigs to save time but it is not numerically stable
% Hx1 = Hx;
% [v1,lambda1] = eigs(Hx,1);
% if isnan(lambda1)
%     [V,D]=eig(Hx);
%     v1 = V(:,1);
%     lambda1 = D(1,1);
% elseif lambda1>0
%     Hx1(1:1+size(Hx1,1):end) = diag(Hx)-lambda1;
%     [v1,lambda2] = eigs(Hx1,1);
%     if isnan(lambda2)
%         [V,D]=eig(Hx);
%         v1 = V(:,1);
%         lambda1 = D(1,1);
%     else
%         lambda1=lambda1+lambda2;
%     end
% end
%Hess = Hess(x,p);%in case explicit Hessian is not available
i=0;
%Cartis et al 2011 Algorithm 2.1 
while norm(gx) > errTol && i < maxIts
    i=i+1;
    p = ARCSubproblem(gx,Hx,v1,lambda1,sigma,kappa_easy,maxIts/10);
    rho  = (fx-f(x+p))/(-m(p,gx,Hx,sigma));
    %successful, move in that direction
    if rho >= eta1
        x = x + p;
%         fprintf('norm(x)=%f\n',norm(x))
        fx = f(x);
        gx = grad(x);
        Hx = H(x);
        [V,D]=eig(Hx);
        v1 = V(:,1);
        lambda1 = D(1,1);
        %eigs
%         Hx1 = Hx;
%         [v1,lambda1] = eigs(Hx,1);
%         if isnan(lambda1)
%             [V,D]=eig(Hx);
%             v1 = V(:,1);
%             lambda1 = D(1,1);
%         elseif lambda1>0
%             Hx1(1:1+size(Hx1,1):end) = diag(Hx)-lambda1;
%             [v1,lambda2] = eigs(Hx1,1);
%             if isnan(lambda2)
%                 [V,D]=eig(Hx);
%                 v1 = V(:,1);
%                 lambda1 = D(1,1);
%             else
%                 lambda1=lambda1+lambda2;
%             end
%         end
        %Hess = Hess(x,p);
        %very successful,expand TR radius
        if rho > eta2
           sigma = max(0.5 * sigma,sigma_min);
        end
    %unsuccessful, shrink TR radius
    else
        sigma = 2 * sigma;
    end
    errHistory(i)     = errFcn(x);
    %hereustic to terminate swamp
    if i > 100 && abs(errHistory(i)-0.5) < 1e-3
        if (max(abs(errHistory(i-50:i)-0.5))+min(abs(errHistory(i-50:i)-0.5)))/2 < 1e-3
            fprintf('Terminated at swamp 0.5.\n');
            return
        end
    elseif i > 100 && abs(errHistory(i)-1) < 1e-3
        if (max(abs(errHistory(i-50:i)-1))+min(abs(errHistory(i-50:i)-1)))/2 < 1e-3
            fprintf('Terminated at swamp 1.\n');
            return
        end
    elseif i > 100 && abs(errHistory(i)-1.5) < 1e-3
        if (max(abs(errHistory(i-50:i)-1.5))+min(abs(errHistory(i-50:i)-1.5)))/2 < 1e-3
            fprintf('Terminated at swamp 1.5.\n');
            return
        end
    end
%         if ~mod( i, iterInterval )
%             fprintf('Iteration %5d, error is %.2e\n', i, errHistory(i) );
%         end
end
%fprintf("sigma=%f\n",sigma);

end