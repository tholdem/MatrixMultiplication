function x = gradientDescent4NormalizedTensorCPD(f,grad,varargin)
%usage: [x,errorHistory] = leastSquaresgradDescent(f, grad, varargin)
%f is the loss function, grad is the grad of loss function
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%parse parameter inputs
p = inputParser;
addParameter(p,'errTol',1e-6,@(x) x>0);
%SRB: allow this to be an optional input (if none supplied, then do random by default; and I would use randn not rand, so that you get some negative values in there)
addParameter(p,'x0',0);
addParameter(p,'maxIts',1e5,@(x) x>0);
addParameter(p,'NormFcn',0);
addParameter(p,'errFcn',0);
addParameter(p,'errDisplay','off');
addParameter(p,'iterInterval',2,@(x) x>0);
parse(p,varargin{:});

errTol = p.Results.errTol;
normalize = p.Results.NormFcn;
x = p.Results.x0;
maxIts  = p.Results.maxIts;
errDispFlag = p.Results.errDisplay;
if errDispFlag == 1
    errFcn = p.Results.errFcn;
    iterInterval = p.Results.iterInterval;
end
sigma = 10;

errorHistory = zeros(maxIts,1);

fx1 = f(x);
fx = fx1 + errTol +1;
 % SRB
i=0;
 % -- SRB: the next few lines you should just do in the while/for loop
 % (the less duplicate code the better -- fewer bugs )
while fx - fx1 > errTol && i < maxIts % SRB: prevent infinite loops due to bugs or numerical issues
    fx  = fx1;
    gx = grad(x);
    alpha = ArmijoLineSearch(f,grad,x,sigma,'errTol',errTol);
    x = normalize(x - alpha*gx);
    fx1 = f(x);
%     fx1 = 0.5*sum((A*x-b).^2); 
    %fx1     = f(x);
    % SRB: in the line above, I would either call the function handle to
    % f(x), or if it is hard-coded to be least-squares, then you can save
    % some computation here because you compute A*x-b, and this will be
    % re-used the next iteration when calculating gx.
    
    i=i+1;
    if errDispFlag == 1
        errorHistory(i)     = errFcn(x);
        if ~mod( i, iterInterval )
            fprintf('Iteration %5d, error is %.2e\n', i, errorHistory(i) );
        end
    end
end

end