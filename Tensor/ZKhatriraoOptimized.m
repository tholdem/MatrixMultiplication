function C = ZKhatriraoOptimized(Z,B,A)
%O(n^5*r) implementation of Z*khatrirao in the gradient computation using
%the kronecker trick
n = size(Z,1);
vec =@(A) A(:);
rank=size(A,2);
C = zeros(1,rank);
for j=1:20
tic
ZM =reshape(Z,[9,81]);
for i=1:n %take each row vector of Z and treat it like u
    for r=1:rank %consider each column of khatrirao which is a kronecker product
        C(i,r)=vec(A(:,r)'*reshape(ZM(i,:)',[n n])*B(:,r)); %applying the trick
    end
end
toc
end
for j=1:20
tic
reshape(Z,[9,81]) * khatriraoOptimized(X(:,:,3), X(:,:,2));
toc
end

end