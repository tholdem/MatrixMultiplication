function idxarray = findMedianIdx(values)
n=size(values,2);
sorted = sort(values);
if mod(n,2)
    idxarray = values==median(values);
else
    idxarray = values==sorted(floor(n/2));
end
end