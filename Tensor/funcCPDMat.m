function ret_val = funcCPDMat(Z,X,U,V,W)
%FUNC_F     Returns function f.
%   This is used with FASTA package.
%edited by Jaden Wang 6/17/2020
% for vectorized input
%X = tensor(ktensor({U(x),V(x),W(x)}));
Y = ktensorOptimized(U(X),V(X),W(X));

ret_val = 1/2 * norm(reshape(Y,[9,81]) - reshape(Z,[9,81]),'fro')^2;

end

