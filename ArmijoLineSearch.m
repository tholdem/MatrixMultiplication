function alpha = ArmijoLineSearch(f,grad,x,alpha,varargin)
%usage: alpha = ArmijoLineSearch(f,fx,gx,x,alpha,varargin), where f is
%the loss function, fx is the loss function value evaluated at x_k
%gx is the gradient at x_k, x is x_k, and alpha
%is the initial positive constant 

p = inputParser;
addParameter(p,'errTol',1e-6,@(x) x>0);
parse(p,varargin{:})
errTol = p.Results.errTol;

c = .0001;
fx=f(x);
gx = grad(x);
gxN2 = norm(gx)^2; % SRB
%rhs = f(x_k)-c*stepsize*inner product of gradient at x_k
rhs = 0;
%lhs = f(x_k - alpha*gx)
lhs = errTol + 1;
%contraction factor in (0.25,0.75)
%rho = 0.25+.5*rand;
% SRB: these are typical ranges (even rho = 0.9 is OK),
%   but usually we fix a rho and do not change it
%   so I would just do this:
rho     = 0.5;  
%i=0
%while abs(lhs - rhs) > errTol
while lhs - rhs > errTol
    %contract step size by rho
    alpha = alpha * rho;
    rhs = fx - c*alpha*gxN2;
    lhs = f(x - alpha*gx); % SRB: again, use norm() not sum()
    %i=i+1
end
end