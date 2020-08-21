function val = productSegreManifoldObjFcn(Z,P,fieldnames)
S=zeros(size(Z));
for i=1:size(fieldnames,1)
    S = S + double(full(P.(fieldnames{i}).X));
end
val = 0.5*frob(S-Z,'squared');
end