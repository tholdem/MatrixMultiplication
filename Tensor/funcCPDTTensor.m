function ret_val = funcCPDTTensor(Z,T)
%FUNC_F     Returns function f.
%   This is used with FASTA package.
%edited by Jaden Wang 6/17/2020
% for vectorized input
%X = tensor(ktensor({U(x),V(x),W(x)}));
X = ktensorOptimized(T.X.U{1},T.X.U{2},T.X.U{3});
% AA = cell(3,1);
% no_row = size(A,1)/3;
% for k = 1:3
%     AA{k} = A(1 + (k-1)*no_row : k*no_row, :);
% end

%ret_val = 1/2 * norm(X - tensor(Z))^2;
ret_val = 1/2 * frob(X - Z,'squared');

end
