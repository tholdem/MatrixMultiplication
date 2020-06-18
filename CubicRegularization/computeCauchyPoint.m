function pc = computeCauchyPoint(gx,Hx,Delta)
%Usage: pc = computeCauchyPoint(gx,Hx,Delta)
%Delta is the trust region radius
if dot(gx,Hx)*gx <= 0
    pc = -Delta/norm(g)*g;
else
    pc = min(norm(g)^3/(Delta*dot(gx,Hx)*gx),1);
end
end