function [x,errorHistory] = gradientDescent(f,gradient,varargin)
%usage: [x,errorHistory] = leastSquaresGradientDescent(f, gradient, varargin)
%f is the loss function, gradient is the gradient of loss function
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
    %compute initial step size using spectral norm of A.'A, which is also the
    %sqrt of its largest eigenvalue
    % sigma = sqrt(max(eig(A.'*A)));
    sigma   = norm(A)^2; % SRB: more efficient
    if x == 0
        x = randn(size(A,2),1);
    end
    errFcn = p.Results.errFcn;
end

errorHistory = zeros(maxIts,1);



fx1 = f(x);
fx = fx1 + errorThd +1;
 % SRB
i=0;
 % -- SRB: the next few lines you should just do in the while/for loop
 % (the less duplicate code the better -- fewer bugs )
while fx - fx1 > errorThd && i < maxIts % SRB: prevent infinite loops due to bugs or numerical issues
    fx  = fx1;
    nabla = gradient(x);
    alpha = ArmijoLineSearch(f,fx,nabla,x,sigma,'errorThd',errorThd);
    x = x - alpha*nabla;
    fx1 = f(x);
%     fx1 = 0.5*sum((A*x-b).^2); 
    %fx1     = f(x);
    % SRB: in the line above, I would either call the function handle to
    % f(x), or if it is hard-coded to be least-squares, then you can save
    % some computation here because you compute A*x-b, and this will be
    % re-used the next iteration when calculating nabla.
    
    i=i+1;
    errorHistory(i)     = errFcn( x );
    if ~mod( i, 20 )
        fprintf('Iteration %5d, error is %.2e\n', i, errorHistory(i) );
    end
    
end

end