function ret_val = func_f(Z,x,U,V,W)
%FUNC_F     Returns function f.
%   This is used with FASTA package.
%edited by Jaden Wang 6/17/2020
% for vectorized input
X = tensor(ktensor({U(x),V(x),W(x)}));
% AA = cell(3,1);
% no_row = size(A,1)/3;
% for k = 1:3
%     AA{k} = A(1 + (k-1)*no_row : k*no_row, :);
% end

ret_val = 1/2 * norm(X - tensor(Z))^2;

end

