function xgc = computeGeneralizedCauchyPoint(x,gx,m,Proj,kappa_ubs,kappa_lbs,kappa_epp,maxIts)
j = 0;
tmin = 0;
tmax = inf;
t = 1;
while j < maxIts
    xgc = Proj(x-t*gx);
    mxgc = m(xgc);
    dp = dot(gx,xgc-x);
    if mxgc > fx + kappa_ubs*dp
        tmax = t;
    elseif mxgc < fx + kappa_lbs*dp && ??? > kappa_epp * abs(dp)
        tmin = t;
    else
        return
    end
    if tmax == inf
        t=2*t;
    else
        t = 0.5*(tmin+tmax);
    end
    j = j+1;
end
end