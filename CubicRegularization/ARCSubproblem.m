function p = ARCSubproblem(gx,B,V,D,sigma,kappa_easy,maxIts)
% Usage: p = ARCSubproblem(gx,B,V,D,sigma,kappa_easy,maxIts)
%adapted from Algorithm 7.3.6, Conn et al 2000, Algorithm 4.3, Nocedal
%and Wright, 2006, and Cartis et al 2011

evals = diag(D);
lambda = max(0,-min(evals));
lambda_const = (1+lambda)*sqrt(eps);
if lambda ~= 0 %strictly greater than
    lambda = lambda + lambda_const;
end
Delta = lambda/sigma;
%garbage value just to pass the condition of while loop
p = 1+kappa_easy+Delta;
i=0;
%we are trying to find the global minimizer of m(p). It should satisfy 
%1. (B+lambda*I)p = -g
%2. lambda^2 = sigma^2*norm(p)
%see Eqn (6.1) in Cartis et al 2011
while abs(norm(p)-Delta)>kappa_easy && i < maxIts
    i=i+1;
    try
        R = chol(B+lambda*eye(size(B)));
    catch
        %if this error occurs it means there is numerical instability with
        %factorization, attempts resolving by incrementing a bit
        %fprintf('ERROR: lambda < - smallest eigenvalue; the Cholesky factorization does not exist.\n');
        lambda = lambda + 2*lambda_const;
        try 
            R = chol(B+lambda*eye(size(B)));
        catch
            %fprintf('ERROR: lambda < - smallest eigenvalue; the Cholesky factorization does not exist. Exiting...\n');
            p = zeros(size(gx)); %no step taken
            return;
        end
    end
    p = -R\(R'\gx);
%     H_inv = V/(D+lambda*eye(size(D)))*V.'; %alternative to Cholesky,slower
%     p = -H_inv*gx;
    normp=norm(p);
    if normp <= Delta
        if lambda == 0 || normp == Delta
            return
        else %"hard case", Nocedal and Wright, 2006 P88 Equation 4.45
            %fprintf('A wild "hard case" appeared!\n');
            hp = [1 0 norm(V(:,2:end)'*gx./(evals(2:end)+lambda))^2-Delta^2];
            tau = max(roots(hp));
            p = tau*V(:,1) + p;
        end
    end
    q = R'\p;
    if lambda < eps 
        lambda = lambda + lambda_const;
    else %Newton method to update lambda, simplified version of phi(lambda)/phi'(lambda) eqn (6.7) and (6.10)
        lambda = lambda + lambda*(normp-Delta)/(normp+Delta*lambda*(norm(q)/normp)^2);
%         lambda = lambda + lambda*(normp-Delta)/(normp+Delta*lambda*(dot(p,H_inv*p)/normp^2));
    end
    Delta = lambda/sigma;
end

end