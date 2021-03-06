function [Z,out] = RARC_HR(T,r,opts)
%BV_RGN_HR Riemannian trust region method with hot restarts.
% 
% Approximates the tensor /T/ by a low-rank tensor of rank /r/ with the 
% RGN-HR method. The output /Z/ contains the norm-balanced factor matrices 
% of the rank-/r/ approximation.
% 
% Alternatively, r is allowed to be a cell array containing the factor 
% matrices of the starting point from whence RGN-HR should start.
%
% The method attempts to minimize the objective function
%
%                  f(z)  = 1/2 * || T - [[z{1},...,z{d}]] ||^2,
%
% where [[z{1},...,z{d}]] is the tensor represented by the factor matrices
% z.
%
% The input argument /opts/ allows the user to set specific options:
%   * opts.MaxIter      The maximum number of objective function 
%                       evaluations.
%   * opts.MaxRestarts  The maximum number of restarts.
%   * opts.TolAbs       Absolute tolerance on the objective function.
%   * opts.TolFun       Relative tolerance on the improvement of the
%                       objective function in successive iterations.
%   * opts.TolX         Relative tolerance on the size of the tangent
%                       vector along which the retraction is performed.
%
% The output /out/ contains the following items:
%   * out.info          A status integer. A positive value means that
%                       RGN-HR was terminated because one of the tolerances
%                       was reached (TolAbs, TolFun, or TolX). A negative
%                       value means that RGN-HR was terminated because of
%                       reaching MaxIter or MaxRestarts. Specifically, 
%                        -2: Maximum number of restarts exceeded.
%                        -1: Maximum number of iterations reached.
%                         1: Step tolerance TolX reached.
%                         2: Function improvement tolerance TolFun reached.
%                         3: Absolute tolerance TolAbs rearched.
%   * out.iterations    The number of objective function evaluations.
%   * out.restarts      The number of hot restarts.
%   * out.condest       Estimate of the condition number of the computed
%                       CPD.
%   * out.fval          The sequence of objective function values.
%   * out.relfval       The sequence of relative function value
%                       improvements.
%   * out.relstep       The sequence of relative step sizes.
%   * out.delta         The sequence of trust region radii.
%   * out.rho           The sequence of trustworthiness values.
%
% This code implements RGN-HR, i.e., the Riemannian Gauss-Newton method 
% with trust region, dogleg step, and hot restarts near ill-conditioned 
% CPDs, as introduced in
%     * Breiding, Vannieuwenhoven, A Riemannian trust region method for the
%       canonical tensor rank approximation problem, SIAM J. Optim., 2018.

residual = @(X,S) cpdgen(X) - S;
F = @(X) 0.5*frob(cpdgen(X) - T,'squared');
normFM = @(X) sqrt(sum(arrayfun(@(k) frob(X{k})^2, 1:length(X))));
m = @(p,gx,Hx,sigma) dot(p,gx) + 0.5 * dot(Hx*p,p) + 1/3*sigma*norm(p)^3;

% Choose random starting point.
Z0 = r;
d = ndims(T);
if ~iscell(Z0)
   Z0 = arrayfun(@(k) randn(size(T,k),r), 1:d, 'UniformOutput', 0);
end
r = size(Z0{1},2);

% Set default options.
if (nargin < 3) || ~isstruct(opts)
   opts = struct; 
end
if ~isfield(opts, 'MaxIter'),     opts.MaxIter = 1000; end
if ~isfield(opts, 'MaxRestarts'), opts.MaxRestarts = opts.MaxIter; end
if ~isfield(opts, 'TolAbs'),      opts.TolAbs = 1e-12; end
if ~isfield(opts, 'TolFun'),      opts.TolFun = 1e-16; end
if ~isfield(opts, 'TolX'),        opts.TolX   = 1e-12; end
if ~isfield(opts, 'sigma'),     opts.simga = 1; end
if ~isfield(opts, 'sigma_min'),   opts.sigma_min = 1e-3; end
if ~isfield(opts, 'eta_1'),       opts.eta_1 = 0.1; end
if ~isfield(opts, 'eta_2'),       opts.eta_2 = 0.9; end
if ~isfield(opts, 'kappa_easy'),     opts.kappa_easy = 1e-3; end

% Prepare the output structure.
out.info = 0;
out.iterations = 0;
out.restarts = 0;
out.condest = 0;
out.fval = F(Z0);
out.relfval = [];
out.relstep = [];
out.sigma = [];
out.rho = [];
out.grad = [];


% Determine optimal coefficients.
x = bv_optimal_coeff(T, Z0);
Z0{1} = Z0{1} * diag(x);
Z0 = bv_norm_balance(Z0);

% Set trust region parameters.
maxsigma = @(x) 1/(0.1*sqrt(1/r)*normFM(x));
minsigma = 1/frob(T);
out.sigma = max(maxsigma(Z0),minsigma);

while ~out.info
       
    trial = 0;
    maxTrials = opts.MaxRestarts - out.restarts;
    Z00=Z0;
    while (trial > -1) && (trial <= maxTrials)
       % Compute Hessian approximation.
       rez = reshape(residual(Z0, T),[],1);
       [JHJ, Us] = bv_H(Z0);

       if trial == 0
           AlphScal = min(.25,10*frob(rez)/frob(T)); 
       end

       % Try to factor and check correctness.
       [L,p] = chol(JHJ,'lower');
       %dg = diag(L);
       if (p > 0) %|| (min(dg) < 1e-8)
           scal = trial * AlphScal;
           trial = trial+1;
           for kk = 1 : d
              Zp = randn(size(Z00{kk}));
              Zp = Zp * diag(arrayfun(@(jj) norm(Z00{kk}(:,jj))/norm(Zp(:,jj)),1:r));
              Z0{kk} = (1-scal)*Z00{kk} + scal*Zp;
           end
          
           % Compute optimal coefficients again.
           x = bv_optimal_coeff(T, Z0);
           Z0{1} = Z0{1}*diag(x);
           Z0 = bv_norm_balance(Z0);
           out.sigma(end) = max(maxsigma(Z0),minsigma);
           out.fval(end) = F(Z0);
       else
           out.restarts = out.restarts + trial;
           trial = -1;
       end
    end
    if trial > maxTrials
       out.restarts = opts.MaxRestarts;
       out.info = -2;
       break;
    end
    % Compute the gradient.
    grad = bv_JtR(Z0,Us,rez);
    [V,D]=eig(JHJ);
    v1 = V(:,1);
    lambda1 = D(1,1);
    sigma = out.sigma(end);
    p = ARCSubproblem(grad,JHJ,v1,lambda1,sigma,opts.kappa_easy,opts.MaxIter/10);
    Z = bv_retraction_sthosvd(Z0, Us, p);
    fval = out.fval(end);
    rho  = (fval-F(Z))/(-m(p,grad,JHJ,sigma));
    %successful, move in that direction
    if rho >= opts.eta_1
        Z0 = Z;
        fval = F(Z);
        %very successful,expand TR radius
        if rho > opts.eta_2
           out.sigma(end+1)= max(0.5 * sigma,opts.sigma_min);
        else
            out.sigma(end+1) = sigma;
        end
    %unsuccessful, shrink TR radius
    else
        out.sigma(end) = 2 * sigma;
    end
    % Check for convergence.
    relstep = norm(p)/normFM(Z0); 
    % Update the output structure.
    out.fval(end+1)  = fval;
    out.rho(end+1)  = rho;
    out.iterations   = length(out.fval);
    out.relfval(end+1) = ...
        abs(diff(out.fval(end:-1:end-1)))/abs(out.fval(1));
    out.relstep(end+1) = relstep;
    out.grad(end+1) = norm(grad);
    if out.iterations >= opts.MaxIter,    out.info = -1; end
    if out.relstep(end) <= opts.TolX,     out.info = 1;  end    
    if out.relfval(end) <= opts.TolFun,   out.info = 2;  end
    if out.fval(end) <= opts.TolAbs,      out.info = 3;  end
end

Z = Z0;
out.condest = bv_condest( Z );

end
