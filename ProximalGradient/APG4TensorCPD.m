function [x1,errHistory] = APG4TensorCPD(f,grad,R,gradR,varargin)

p = inputParser;
addParameter(p,'errTol',1e-6,@(x) x>0);
addParameter(p,'x0',0);
addParameter(p,'t0',0);
addParameter(p,'t1',1);
addParameter(p,'alpha',10);
addParameter(p,'maxIts',1e5,@(x) x>0);
addParameter(p,'errFcn',0);
addParameter(p,'U',0);
addParameter(p,'V',0);
addParameter(p,'W',0);

parse(p,varargin{:});

errTol = p.Results.errTol;
x0 = p.Results.x0;
maxIts  = p.Results.maxIts;
errFcn = p.Results.errFcn;
t0 = p.Results.t0;
t1 = p.Results.t1;
alpha = p.Results.alpha;
U = p.Results.U;
V = p.Results.V;
W = p.Results.W;
errHistory = zeros(maxIts,1);

L2 = @(x,z,rho) 1/(2*rho) * norm(x-z)^2;
gradL2 = @(x,z,rho) 1/rho * (x-z);
vec = @(A) A(:);

% normalize = @(A) A./sum(A.^2,1).^0.5;
normalize = @(x) [vec(U(x)./sum(U(x).^2,1).^0.5);vec(V(x)./sum(V(x).^2,1).^0.5);vec(W(x)./sum(W(x).^2,1).^0.5)];

F = @(x) f(x) + R(x); 
% Ux=normalize(U(x));
% Vx=normalize(V(x));
% Wx=normalize(W(x));

x1=x0;
z1=x1;
k=1;
while k <= maxIts
    % gradient step
    y = x1+t0/t1*(z1-x1)+(t0-1)/t1*(x1-x0);
    t0 = t1;
    t1 = (sqrt(4*t1^2+1)+1)/2;
    %gradient step
    gy = grad(y);
    rho = ArmijoLineSearch(f,grad,y,alpha,'errTol',errTol);
    z1 = normalize(y - rho*gy);
    % proximal step
    pf = @(x) R(x) + L2(x,z1,rho);
    gradPf = @(x) gradR(x) + gradL2(x,z1,rho);
%     pf = @(x) R(x) + 1/(2*rho) * norm(x-z1)^2;
%     gradPf = @(x) gradR(x) + 1/rho * (x-z1);
    z2 = normalize(gradientDescent4NormalizedTensorCPD(pf,gradPf,'x0',z1,'NormFcn',normalize));
    if F(z2)<F(x1)
        x0 = x1;
        x1 = z2;
    else
        x0 = x1;
    end
    if norm(grad(x1)) < errTol
        return
    end
    errHistory(k) = errFcn(x1);
    k = k + 1;
end
end