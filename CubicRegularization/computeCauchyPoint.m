function pc = computeCauchyPoint(gx,Hx,Delta)
if dot(gx,Hx)*gx <= 0
    pc = -Delta/norm(g)*g;
else
    pc = min(norm(g)^3/(Delta*dot(gx,Hx)*gx),1);
end
end