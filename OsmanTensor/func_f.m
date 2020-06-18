function ret_val = func_f(A,x,r)
%FUNC_F     Returns function f.
%   This is used with FASTA package.
%edited by Jaden Wang 6/17/2020
% for vectorized input
X = {x(1:9*r),x(9*r+1:18*r),x(18*r+1:27*r)};
AA = cell(3,1);
no_row = size(A,1)/3;
for k = 1:3
    AA{k} = A(1 + (k-1)*no_row : k*no_row, :);
end

ret_val = 1/2 * norm(tensor(ktensor(X)) - tensor(ktensor(AA)))^2;

end

