function C = scaledKhatriraoOptimized(A,B,kv)%#codegen
C = zeros(size(A,1)*size(B,1),size(B,2));
if size(A,2)~=size(B,2)
    fprintf("Error: column dimensions of input matrices don't match.\n")
    return
end
vec=@(A) A(:);
%column-wise kronecker
for j=1:size(B,2)
    C(:,j) = kv(j) * real(vec(kron(A(:,j),B(:,j))));
end
end

