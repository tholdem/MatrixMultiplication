function [p,subout] = ARCSubproblem(gx,B,v1,lambda1,sigma,kappa_easy,maxIts) %#codegen
% Usage: p = ARCSubproblem(gx,B,v1,lambda1,sigma,kappa_easy,maxIts)
%adapted from Algorithm 7.3.6, Conn et al 2000, Algorithm 4.3, Nocedal
%and Wright, 2006, and Cartis et al 2011

%s_out returns -1 if Hessian is ill-conditioned, 0 if maxIts is reached, 1 
%if a good solution is found, 2 if an edge case is reached

%contrain maxIts to save time, remove this if time isn't a concern
maxIts=max(100,min(500,maxIts));
lambda = max(0,-lambda1);
%small value to resolve numerical instability from eig and chol
if lambda ~= 0 %strictly greater than
    lambda = lambda + eps;
end
Delta = lambda/sigma;

B1=B;
i=0;

%we are trying to find the global minimizer of m(p). It should satisfy 
%1. (B+lambda*I)p = -g
%2. lambda^2 = sigma^2*norm(p)
%see Eqn (6.1) in Cartis et al 2011
while i < maxIts
    i=i+1;
    B1(1:1+size(B1,1):end) = real(diag(B)+lambda);
    [R,flag] = chol(B1);
%     [R,flag] = chol(B+lambda*eye(size(B))); %too slow
    k = 0;
    lambda_const = eps;
    while flag ~= 0
        k = k+1;
        %if this error occurs it means there is numerical instability with
        %factorization, attempts resolving by incrementing a bit
%         fprintf('ERROR: lambda=%g < - smallest eigenvalue; the Cholesky factorization does not exist.\n',lambda);
%         lambda = lambda + 2*lambda_const;
%         [R,flag] = chol(B+lambda*eye(size(B)));
        B1(1:1+size(B1,1):end) = real(diag(B1)+lambda_const);
        [R,flag] = chol(B1);
%         if flag ~= 0
% %             fprintf('ERROR: lambda < - smallest eigenvalue; the Cholesky factorization does not exist. Return zeros...\n');
%             p = zeros(size(gx)); %no step taken
%             return;
%         end
        % gradually increase the constant to reduce iterations
        lambda_const = min(lambda_const*2,abs(lambda1));
        if k > maxIts
            p = zeros(size(gx));
            subout.info = -1;
            return
        end
    end
    p = real(-R\(R'\gx));
%     H_inv = V/(D+lambda*eye(size(D)))*V.'; %alternative to Cholesky,slower
%     p = -H_inv*gx;
    normp = norm(p);
    if abs(normp-Delta) < kappa_easy
        % 1 = good solution found
        subout.iters = i;
        subout.info = 1;
        return
    end
    if normp <= Delta
        if lambda == 0 || normp == Delta
            subout.iters = i;
            %2 = edge case
            subout.info = 2;
            return
        else %"hard case", Nocedal and Wright, 2006 P88 Equation 4.45
            %also see Algorithm 7.3.6, P199 of Conn 2000
            %fprintf('A wild "hard case" appeared!\n');
            %1*tau^2+0*tau+(norm^2-Delta^2)=0
            %normp is the same as the expression cuz the first eigenvector
            %dot gx is zero
            %hp = [1 0 norm(V(:,2:end)'*gx./(evals(2:end)+lambda))^2-Delta^2];
            hp = [1 0 normp^2-Delta^2];
            tau = max(real(roots(hp)));
            p = tau*v1 + p;
        end
    end
    q = R'\p;
    if lambda < eps 
        lambda = lambda + lambda_const;
    else
        %Newton method to update lambda, simplified version of phi(lambda)/phi'(lambda) eqn (6.7) and (6.10) in Nocedal
        %and Wright
        lambda = lambda + lambda*(normp-Delta)/(normp+Delta*lambda*(norm(q)/normp)^2);
%         lambda = lambda + lambda*(normp-Delta)/(normp+Delta*lambda*(dot(p,H_inv*p)/normp^2));
%         %equivalent but more expensive
    end
    Delta = lambda/sigma;
end
% 0 = maxIts reached
subout.info = 0;

end