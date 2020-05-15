function [x, errorHistory] = FISTA(f,fgradient,g,varargin)

%parse parameter inputs
p = inputParser;
addParameter(p,'errorThd',1e-6,@(x) x>0);
%SRB: allow this to be an optional input (if none supplied, then do random by default; and I would use randn not rand, so that you get some negative values in there)
addParameter(p,'initialPoint',0);
addParameter(p,'maxIts',1e5,@(x) x>0);
addParameter(p,'algo','leastsquares');
addParameter(p,'matrix',0);
addParameter(p,'errFcn',0);

parse(p,varargin{:});

errorThd = p.Results.errorThd;
x = p.Results.initialPoint;
maxIts  = p.Results.maxIts;
algo = p.Results.algo;

if algo == 'leastsquares'
    A = p.Results.matrix;
    %compute step size using spectral norm of A.'A
    L_old   = norm(A); 
    if x == 0
        x = randn(size(A,2),1);
    end
    errFcn = p.Results.errFcn;
else
    L_old = 1;
end

y = x;
errorHistory = zeros(maxIts,1);


%prox = @(x,y,f,alpha) alpha*f(x) + 1/2*norm(x - y)^2;
%in least squares when g(x)=0, T becomes the identity function
T = @(y,nablaY,L) y - 1/L*nablaY; 
%T = @(y,nablaY,L) prox(y,y-1/L*nablaY,g,1/L);
t = 1;
h = @(t) (1+sqrt(1+4*t^2))/2;

fx = f(x);
fx_old = fx + errorThd + 1;
i=0;

while fx - fx_old > errorThd && i < maxIts
    nablaY = fgradient(y);
    %in least squares, L=sigma since while loop stops at k=1
    L = backtrackingB3(f,T,y,nablaY,L_old,'errorThd',errorThd);
    x_old = x;
    fx_old = fx;
    %update x,fx
    x = T(y,nablaY,L);
    fx = f(x);
    L_old = L;
    %update y
    t_old = t;
    t = h(t);
    y = x +((t_old - 1)/t)*(x - x_old);

    i=i+1;
    errorHistory(i)     = errFcn( x );
    if ~mod( i, 5 )
        fprintf('Iteration %5d, error is %.2e\n', i, errorHistory(i) );
    end
    
end


end