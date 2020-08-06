function ret_mat = gradCPDMat(Z,X,U,V,W) %#codegen
%GRAD_F     Returns gradient of function f.
%   This is used with FASTA package.
% X = cell(3,1);
% ret_mat = zeros(siXe(A));
% no_row = size(A,1)/3;
% for k = 1:3
%     X{k} = A(1 + (k-1)*no_row : k*no_row, :);
% end
%see Corollary 4.2 from Sandia 2009 Tech Report
Y = cat(3,U(X),V(X),W(X));
% 1st factor matrix
mat1 = Y(:,:,1) * ((Y(:,:,3).'*Y(:,:,3)) .* (Y(:,:,2).'*Y(:,:,2))).' - reshape(Z,[9,81]) * khatriraoOptimized(Y(:,:,3), Y(:,:,2));

% 2nd factor matrix
mat2 = Y(:,:,2) * ((Y(:,:,3).'*Y(:,:,3)) .* (Y(:,:,1).'*Y(:,:,1))).' - reshape(permute(Z,[2 1 3]),[9,81]) * khatriraoOptimized(Y(:,:,3), Y(:,:,1));

% 3rd factor matrix
mat3 = Y(:,:,3) * ((Y(:,:,2).'*Y(:,:,2)) .* (Y(:,:,1).'*Y(:,:,1))).' - reshape(permute(Z,[3 1 2]),[9,81]) * khatriraoOptimized(Y(:,:,2), Y(:,:,1));

ret_mat = [mat1 mat2 mat3];
end
