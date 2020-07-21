function ret_vec = grad_f(Z,x,U,V,W) %#codegen
%GRAD_F     Returns gradient of function f.
%   This is used with FASTA package.
% X = cell(3,1);
% ret_mat = zeros(siXe(A));
% no_row = size(A,1)/3;
% for k = 1:3
%     X{k} = A(1 + (k-1)*no_row : k*no_row, :);
% end
%see Corollary 4.2 from Sandia 2009 Tech Report
X = {U(x),V(x),W(x)};
% 1st factor matrix
mat1 = X{1} * ((X{3}.'*X{3}) .* (X{2}.'*X{2})).' - double(tenmat(Z,1)) * khatrirao(X{3}, X{2});

% 2nd factor matrix
mat2 = X{2} * ((X{3}.'*X{3}) .* (X{1}.'*X{1})).' - double(tenmat(Z,2)) * khatrirao(X{3}, X{1});

% 3rd factor matrix
mat3 = X{3} * ((X{2}.'*X{2}) .* (X{1}.'*X{1})).' - double(tenmat(Z,3)) * khatrirao(X{2}, X{1});

ret_vec = [mat1(:);mat2(:);mat3(:)];
end

