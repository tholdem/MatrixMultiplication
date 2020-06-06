function p = ARCSubproblem(gx,B,sigma,kappa_easy,maxIts)
% Usage: p = ACRSubproblem(gx,Hx,Delta)
%adapted from Algorithm 7.3.6, Conn et al 2000, and Algorithm 4.3, Nocedal
%and Wright, 2006
[V,D] = eig(B);
evals = diag(D);
lambda = max(0,-min(evals));
lambda_const = (1+lambda)*sqrt(eps);
if lambda ~= 0 %strictly greater than
    lambda = lambda + lambda_const;
end
Delta = lambda/sigma;
p = 1+kappa_easy+Delta;
i=0;
while abs(norm(p)-Delta)>kappa_easy && i < maxIts
    i=i+1;
    try
        R = chol(B+lambda*eye(size(B)));
    catch
        fprintf('lambda < - smallest eigenvalue; the Cholesky factorization does not exist.\n');
        return
    end
    p = -R\(R'\gx);
    normp=norm(p);
    if normp <= Delta
        if lambda == 0 || normp == Delta
            return
        else %"hard case", Nocedal and Wright, 2006 P88 Equation 4.45
            fprintf('A wild hard case appeared!\n');
            hp = [1 0 norm(V(:,2:end)'*gx./(evals(2:end)+lambda))^2-Delta^2];
            tau = max(roots(hp));
            p = tau*V(:,1) + p;
        end
    end
    q = R'\p;
    if lambda < eps 
        lambda = lambda + lambda_const;
    else %Newton method to update lambda
        lambda = lambda + lambda*(normp-Delta)/(normp+Delta*lambda*(norm(q)/normp)^2);
    end
    Delta = lambda/sigma;
end
end