function ret_mat = grad_f(A, X)
%GRAD_F     Returns gradient of function f.
%   This is used with FASTA package.
AA = cell(3,1);
ret_mat = zeros(size(A));
no_row = size(A,1)/3;
for k = 1:3
    AA{k} = A(1 + (k-1)*no_row : k*no_row, :);
end

% 1st factor matrix
ret_mat(1:no_row, :) = AA{1} * ((AA{3}.'*AA{3}) .* (AA{2}.'*AA{2})).' - double(tenmat(X,1)) * khatrirao(AA{3}, AA{2});

% 2nd factor matrix
ret_mat(no_row+1 : 2*no_row, :) = AA{2} * ((AA{3}.'*AA{3}) .* (AA{1}.'*AA{1})).' - double(tenmat(X,2)) * khatrirao(AA{3}, AA{1});

% 3rd factor matrix
ret_mat(2*no_row+1 : 3*no_row, :) = AA{3} * ((AA{2}.'*AA{2}) .* (AA{1}.'*AA{1})).' - double(tenmat(X,3)) * khatrirao(AA{2}, AA{1});

end

