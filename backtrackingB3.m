function L = backtrackingB3(f,T,y,grady,L,varargin)
%usage: L = backtrackingB3(f,T,y,grady,L,varargin), where f is
%the loss function, T is the prox operator, y is y_k,
%grady is the gradient at y_k, and L
%is the initial positive constant 

p = inputParser;
addParameter(p,'errTol',1e-6,@(x) x>0);
addParameter(p,'maxIts',1e5,@(x) x>0);
parse(p,varargin{:})
errTol = p.Results.errTol;
maxIts = p.Results.maxIts;
%expansion factor
eta = 2;
%L_0 = L_-1
L = L / eta;
rhs = 0;
lhs = errTol + 1;
i=0;
while lhs - rhs > errTol && i < maxIts
    L = eta * L;
    %1st order taylor approximation
    lhs = f(T(y,grady,L));
    %proximal approximation
    rhs = f(y) + grady.'*(T(y,grady,L) - y)+L/2*norm(T(y,grady,L) - y)^2;
    i = i + 1;
end

end