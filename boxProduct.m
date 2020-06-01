function P = boxProduct(A,B)
%Usage: P = boxProduct(A,B)
%if dim(A)=(m1,n1), dim(B)=(m2,n2), then dim(P)=(m1*m2,n1*n2)

[m1,n1] = size(A);
[m2,n2] = size(B);
P = zeros(m1*m2,n1*n2);
for i=1:m1
    for j=1:m2
        for l=1:n1
            for k=1:n2
                P((i-1)*m2+j,(k-1)*n1+l) = A(i,l)*B(j,k);
            end
        end
    end
end
end