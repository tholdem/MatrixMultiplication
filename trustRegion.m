function trustRegion(f,g,H,m,DeltaMax,eta,varargin)
%TODO
p = inputParser;
addParameter(p,'errorThd',1e-6,@(x) x>0);
%SRB: allow this to be an optional input (if none supplied, then do random by default; and I would use randn not rand, so that you get some negative values in there)
addParameter(p,'initialPoint',0);
addParameter(p,'maxIts',1e5,@(x) x>0);
addParameter(p,'algo',2);
addParameter(p,'rank',0);
addParameter(p,'errFcn',0);
addParameter(p,'iterInterval',2,@(x) x>0);
parse(p,varargin{:});

errorThd = p.Results.errorThd;
x = p.Results.initialPoint;
maxIts  = p.Results.maxIts;
iterInterval = p.Results.iterInterval;
algo = p.Results.algo;

Delta = 0;
while fx1 - fx > errorThd
   p = TRSubproblem() 
   rho  = (f(x)-f(x+p))/(m(0)-m(p));
   if rho < 0.25
       Delta = 0.25 * Delta;
   else
       if rho > 0.75 && norm(p) == Delta
           Delta = min(2*Delta,DeltaMax);
       end
       if rho > eta
           x = x + p;
       end
   end
end
end