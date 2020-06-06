function p = TRSubproblem(gx,B,Delta)
% p = TRSubproblem(gx,Hx,Delta)
[V,D] = eig(B);
evals = diag(D);
lambda = max(0,-min(evals));
for l = 1:3
    try
        R = chol(B+lambda*eye(size(B)));
    catch
        fprintf('lambda < - smallest eigenvalue; the Cholesky factorization does not exist.\n');
        return
    end
    p = -R\(R'\gx);
    if norm(p)<= Delta
        if lambda == 0 || norm(p) == Delta
            return
        else %hard case
            hp = [1 0 norm(V(:,2:end)'*gx./(evals(2:end)+lambda))^2-Delta^2];
            tau = max(roots(hp));
            p = tau*V(:,1) + p;
        end
    end
    q = R'\p;
    lambda = lambda + (norm(p)/norm(q))^2 * (norm(p)-Delta)/Delta;
end
end
