function P = productSegreManifoldGrad(Z,P,fieldnames) %#codegen
%GRAD_F     Returns gradient of function f.
%   This is used with FASTA package.
% X = cell(3,1);
% ret_mat = zeros(siXe(A));
% no_row = size(A,1)/3;
% for k = 1:3
%     X{k} = A(1 + (k-1)*no_row : k*no_row, :);
% end
%see Corollary 4.2 from Sandia 2009 Tech Report
r = size(fieldnames,1);
Y = zeros(size(Z,1),r,3);
for i=1:r
    Y(:,i,1) = double(P.(fieldnames{i}).X.core)^(1/3)*P.(fieldnames{i}).X.U{1};
    Y(:,i,2) = double(P.(fieldnames{i}).X.core)^(1/3)*P.(fieldnames{i}).X.U{2};
    Y(:,i,3) = double(P.(fieldnames{i}).X.core)^(1/3)*P.(fieldnames{i}).X.U{3};
end
% 1st factor matrix
mat1 = Y(:,:,1) * ((Y(:,:,3).'*Y(:,:,3)) .* (Y(:,:,2).'*Y(:,:,2))).' - reshape(Z,[9,81]) * khatriraoOptimized(Y(:,:,3), Y(:,:,2));

% 2nd factor matrix
mat2 = Y(:,:,2) * ((Y(:,:,3).'*Y(:,:,3)) .* (Y(:,:,1).'*Y(:,:,1))).' - reshape(permute(Z,[2 1 3]),[9,81]) * khatriraoOptimized(Y(:,:,3), Y(:,:,1));

% 3rd factor matrix
mat3 = Y(:,:,3) * ((Y(:,:,2).'*Y(:,:,2)) .* (Y(:,:,1).'*Y(:,:,1))).' - reshape(permute(Z,[3 1 2]),[9,81]) * khatriraoOptimized(Y(:,:,2), Y(:,:,1));

for i=1:r
    norm1=norm(mat1(:,i));
    norm2=norm(mat1(:,i));
    norm3=norm(mat1(:,i));
    pnorm = norm1*norm2*norm3;
    P.(fieldnames{i}).Cpinv = {1/pnorm,1/pnorm,1/pnorm};
    P.(fieldnames{i}).X.core = tensor(pnorm,[1 1 1]);
    P.(fieldnames{i}).X.U{1} = mat1(:,i);
    P.(fieldnames{i}).X.U{2} = mat2(:,i);
    P.(fieldnames{i}).X.U{3} = mat3(:,i);
end
end
