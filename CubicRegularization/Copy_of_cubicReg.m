function [x,errHistory] = cubicReg(f,grad,varargin) %#codegen
%Usage: [x,errFcn] = cubicReg(f,grad,varargin)
%most code is adapted from this python implementation
%https://github.com/cjones6/cubic_reg/blob/2d1ed4c156bdfc34159b374a264012f3fe79adfe/src/cubic_reg.py#L258
%citations include:
%C. Cartis, N. I. M. Gould, and P. L. Toint, “Adaptive cubic regularisation methods for unconstrained optimization. Part I: Motivation, convergence and numerical results,” Math. Program., vol. 127, no. 2, pp. 245–295, 2011.
%Conn, A. R., Gould, N. I., & Toint, P. L. (2000). Trust region methods (Vol. 1). Siam.
p = inputParser;
addParameter(p,'errThd',1e-6,@(x) x>0);
addParameter(p,'x0',0);
addParameter(p,'eta',0.25);
addParameter(p,'Delta',0.25);
addParameter(p,'Delta_hat',0.25);
addParameter(p,'sigma0',1);
addParameter(p,'eta1',0.1);
addParameter(p,'eta2',0.9);
addParameter(p,'kappa_easy',0.0001);
%needed for supplying x0 if not provided
addParameter(p,'matrix',0);
addParameter(p,'rank',0);
addParameter(p,'method',"adaptive");
addParameter(p,'HessianMethod',"exact");
%exact explicit hessian
addParameter(p,'Hessian',0);
%exact implicit Hessian to save computation
%addParameter(p,'implicitHessian',0);
addParameter(p,'maxIts',1e5,@(x) x>0);
addParameter(p,'errFcn',0);
addParameter(p,'iterInterval',2,@(x) x>0);
% addParameter(p,'projection','off');
% addParameter(p,'projFcn',0);
addParameter(p,'penalty','off');


parse(p,varargin{:});

errThd = p.Results.errThd;
x = p.Results.x0;

H = p.Results.Hessian;
%Hess = p.Results.implicitHessian;
maxIts  = p.Results.maxIts;
%iterInterval = p.Results.iterInterval;
method = p.Results.method;

A = p.Results.matrix;
r = p.Results.rank;
if x == 0
    x = randn(r*(size(A,1)+size(A,2)),1);
end
errFcn = p.Results.errFcn;
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

sigma = p.Results.sigma0;
eta1 = p.Results.eta1;
eta2 = p.Results.eta2;
kappa_easy = p.Results.kappa_easy;

%if method == "original" %unfinished
%     Delta = p.Results.Delta;
%     Delta_hat = p.Results.Delta_hat;
%     eta = p.Results.eta;
%     fx = f(x);
%     gx = grad(x);
%     Hx = H(x);
%     i=0;
%     while norm(gx) > errThd && i < maxIts
%         i=i+1;
%         p = TRSubproblem(gx,Hx,Delta);
%         rho  = (fx-f(x+p))/-m(p,gx,Hessx,sigma);
%         %successful, move in that direction
%         if rho >= 0.25
%             x = x + p;
%             %gx = grad(x);
%             fx = f(x);
%             gx = grad(x);
%             Hx = H(x);
%             Hessx = Hess(x,x);
%             %very successful,expand TR radius
%             if rho > 0.75 && norm(p) == Delta
%                Delta = min(2 * Delta, Delta_hat);
%             end
%         %unsuccessful, shrink TR radius
%         else
%             Delta = .25 * Delta;
%         end
%         if rho > eta
%             x = x + p;
%         end
%     end
% if method == "projection" %unfinished
%     fx = f(x);
%     gx = grad(x);
%     Hx = H(x);
%     %Hess = Hess(x,p);%in case explicit Hessian is not available
%     i=0;
%     %Cartis et al 2011 Algorithm 2.1 
%     while norm(gx) > errThd && i < maxIts
%         i=i+1;
%         p = ARCSubproblem(gx,Hx,sigma,kappa_easy,maxIts);
%         pc = computeCauchyPoint(gx,Hx,)
%         rho  = (fx-f(x+p))/(-m(p,gx,Hx,sigma));
%         fprintf('rho=%f, numerator=%f,denom=%f\n',rho,(fx-f(x+p)),-m(p,gx,Hx,sigma))
%         %successful, move in that direction
%         if rho >= eta1
%             x = Proj(x + p);
%             fx = f(x);
%             gx = grad(x);
%             Hx = H(x);
%             %Hess = Hess(x,p);
%             %very successful,expand TR radius
%             if rho > eta2
%                sigma = 0.5 * sigma;
%             end
%         %unsuccessful, shrink TR radius
%         else
%             sigma = 2 * sigma;
%         end
%         errHistory(i)     = errFcn(x);
%         if ~mod( i, iterInterval )
%             fprintf('Iteration %5d, error is %.2e\n', i, errHistory(i) );
%         end
%     end    
if method == "adaptive"
    fx = f(x);
    gx = grad(x);
    Hx = H(x);
    [V,D] = eig(Hx);
    %Hess = Hess(x,p);%in case explicit Hessian is not available
    i=0;
    %Cartis et al 2011 Algorithm 2.1 
    while norm(gx) > errThd && i < maxIts
        i=i+1;
        p = ARCSubproblem(gx,Hx,V,D,sigma,kappa_easy,maxIts/10);
        rho  = (fx-f(x+p))/(-m(p,gx,Hx,sigma));
        %successful, move in that direction
        if rho >= eta1
            %x = Proj(x + p);
            x = x + p;
            %fprintf('norm(x)=%f\n',norm(x))
            fx = f(x);
            gx = grad(x);
            Hx = H(x);
            [V,D] = eig(Hx);
            %Hess = Hess(x,p);
            %very successful,expand TR radius
            if rho > eta2
               sigma = 0.5 * sigma;
            end
        %unsuccessful, shrink TR radius
        else
            sigma = 2 * sigma;
        end
        errHistory(i)     = errFcn(x);
%         if ~mod( i, iterInterval )
%             fprintf('Iteration %5d, error is %.2e\n', i, errHistory(i) );
%         end
    end
    %fprintf("sigma=%f\n",sigma);
end
end