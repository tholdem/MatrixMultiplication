function [x, errorHistory] = FISTA(f,fgradient,g,varargin)
%g is regularization term
%parse parameter inputs
p = inputParser;
addParameter(p,'errorThd',1e-6,@(x) x>0);
addParameter(p,'initialPoint',0);
addParameter(p,'maxIts',1e5,@(x) x>0);
addParameter(p,'algo',0);
addParameter(p,'matrix',0);
addParameter(p,'errFcn',0);
addParameter(p,'iterInterval',2,@(x) x>0);

parse(p,varargin{:});

errorThd = p.Results.errorThd;
x = p.Results.initialPoint;
maxIts  = p.Results.maxIts;
algo = p.Results.algo;
iterInterval = p.Results.iterInterval;

if algo == 'leastsquares'
    A = p.Results.matrix;
    %compute step size using spectral norm of A.'A
    L   = norm(A)^2; 
    if x == 0
        x = randn(size(A,2),1);
    end
    errFcn = p.Results.errFcn;
else
    L = 10;
end

y = x;
errorHistory = zeros(maxIts,1);


%prox = @(x,y,f,alpha) alpha*f(x) + 1/2*norm(x - y)^2;
%in least squares when g(x)=0, T becomes the identity function
T = @(y,nablaY,L) y - 1/L*nablaY; 
%T = @(y,nablaY,L) prox(y,y-1/L*nablaY,g,1/L);
t = 1;
h = @(t) (1+sqrt(1+4*t^2))/2;
x_old = zeros(size(x));

i=0;

while norm(x_old - x) > errorThd && i < maxIts
    nablaY = fgradient(y);
    %set initial L_k=L_{k-1} and compute via backtracking
    L = backtrackingB3(f,T,y,nablaY,L,'errorThd',errorThd);
    x_old = x;
    %update x, which L to use? textbook example says 1/L but the original
    %formula was just L, tried both and neither worked
    x = T(y,nablaY,L);
    %update y
    t_old = t;
    t = h(t);
    y = x +((t_old - 1)/t)*(x - x_old);

    i=i+1;
    errorHistory(i)     = errFcn( x );
    if ~mod( i, iterInterval )
        fprintf('Iteration %5d, error is %.2e\n', i, errorHistory(i) );
    end
    
end


end