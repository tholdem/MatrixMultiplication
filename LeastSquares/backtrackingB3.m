function L = backtrackingB3(f,T,y,nablaY,L,varargin)
%usage: L = backtrackingB3(f,T,y,nablaY,L,varargin), where f is
%the loss function, T is the prox operator, y is y_k,
%nablaY is the gradient at y_k, and L
%is the initial positive constant 

p = inputParser;
addParameter(p,'errorThd',1e-6,@(x) x>0);
addParameter(p,'maxIts',1e5,@(x) x>0);
parse(p,varargin{:})
errorThd = p.Results.errorThd;
maxIts = p.Results.maxIts;
%expansion factor
eta = 2;
%L_0 = L_-1
L = L / eta;
rhs = 0;
lhs = errorThd + 1;
i=0;
while lhs - rhs > errorThd && i < maxIts
    L = eta * L;
    lhs = f(T(y,nablaY,L));
    rhs = f(y) + nablaY.'*(T(y,nablaY,L) - y)+L/2*norm(T(y,nablaY,L) - y)^2;
    i = i + 1;
end

end