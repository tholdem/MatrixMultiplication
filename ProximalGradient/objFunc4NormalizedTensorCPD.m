function val = objFunc4NormalizedTensorCPD(Z,x,U,V,W,lambdav)

X = scaledKtensorOptimized(U(x),V(x),W(x),lambdav(x));
% AA = cell(3,1);
% no_row = size(A,1)/3;
% for k = 1:3
%     AA{k} = A(1 + (k-1)*no_row : k*no_row, :);
% end

%ret_val = 1/2 * norm(X - tensor(Z))^2;
val = 1/2 * norm(reshape(X,[9,81]) - reshape(Z,[9,81]),'fro')^2;

end