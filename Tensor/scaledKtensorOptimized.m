function D = scaledKtensorOptimized(A,B,C,kv)%#codegen
%sum of columnwise outer products
if size(A,2)~=size(B,2) || size(A,2)~=size(C,2)
    fprintf("Error: column dimensions of input matrices don't match.\n")
    D = zeros(9,9,9);
    return
end
%compute the matricized tensor using KhatriRao product (see Sandia
%technical paper 2009), flatten over mode-3
D = reshape((C * scaledKhatriraoOptimized(B,A,kv).').',[9,9,9]);
end