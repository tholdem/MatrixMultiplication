function vec = gradient4NormalizedTensorCPD(Z,x,U,V,W,lambdav)
X = cat(3,U(x),V(x),W(x));
lambda = lambdav(x);
lambdaG = lambda * lambda.';
% 1st factor matrix
mat1 = X(:,:,1) * ((X(:,:,3).'*X(:,:,3)) .* (X(:,:,2).'*X(:,:,2)) .* lambdaG).' - reshape(Z,[9,81]) * scaledKhatriraoOptimized(X(:,:,3), X(:,:,2),lambda);

% 2nd factor matrix
mat2 = X(:,:,2) * ((X(:,:,3).'*X(:,:,3)) .* (X(:,:,1).'*X(:,:,1)) .* lambdaG).' - reshape(permute(Z,[2 1 3]),[9,81]) * scaledKhatriraoOptimized(X(:,:,3), X(:,:,1),lambda);

% 3rd factor matrix
mat3 = X(:,:,3) * ((X(:,:,2).'*X(:,:,2)) .* (X(:,:,1).'*X(:,:,1)) .* lambdaG).' - reshape(permute(Z,[3 1 2]),[9,81]) * scaledKhatriraoOptimized(X(:,:,2), X(:,:,1),lambda);

vec = [mat1(:);mat2(:);mat3(:)];


end