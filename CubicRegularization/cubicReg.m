function [x,errFcn] = cubicReg(f,gradient,varargin)
p = inputParser;
addParameter(p,'errorThd',1e-6,@(x) x>0);
%SRB: allow this to be an optional input (if none supplied, then do random by default; and I would use randn not rand, so that you get some negative values in there)
addParameter(p,'initialPoint',0);
addParameter(p,'maxIts',1e5,@(x) x>0);
addParameter(p,'algo',2);
addParameter(p,'matrix',0);
addParameter(p,'rank',0);
addParameter(p,'errFcn',0);
addParameter(p,'iterInterval',2,@(x) x>0);
parse(p,varargin{:});

errorThd = p.Results.errorThd;
x = p.Results.initialPoint;
maxIts  = p.Results.maxIts;
iterInterval = p.Results.iterInterval;
algo = p.Results.algo;

%leastsquares
if algo == 1
    A = p.Results.matrix;
    %compute initial step size using spectral norm of A.'A, which is also the
    %sqrt of its largest eigenvalue
    % sigma = sqrt(max(eig(A.'*A)));
    sigma   = norm(A)^2; % SRB: more efficient
    if x == 0
        x = randn(size(A,2),1);
    end
    errFcn = p.Results.errFcn;
%SVD
elseif algo == 2
    A = p.Results.matrix;
    r = p.Results.rank;
    sigma   = 1; % no best starting point
    if x == 0
        x = randn(r*(size(A,1)+size(A,2)),1);
    end
    errFcn = p.Results.errFcn;
end

errorHistory = zeros(maxIts,1);



end