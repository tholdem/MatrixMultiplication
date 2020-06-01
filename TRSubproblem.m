function TRSubproblem()
for l = 1:3
    R = chol(B+lambda*eye(size(B)));
    p = -R\(R'\gx);
    q = R'\p;
    lambda = lambda + (norm(p)/norm(q))^2 * (norm(p)-Delta)/Delta;
end