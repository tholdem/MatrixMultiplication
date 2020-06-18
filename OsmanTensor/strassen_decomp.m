function Y = strassen_decomp()
% STRASSEN_DECOMP Create the CP tensor corresponding to Strassen.
%
%   This function requires Tensor Toolbox version 2.6 [Ba15].
%
%   Y = STRASSEN_DECOMP() returns the tensor corresponding to the Strassen
%   matrix multiplication algorithm. Specifically, this is the version of
%   the algorithm described in Section 1.3.11 in [Go13]. The output Y is a
%   cell containing the factor matrices corresponding to the tensor.
%   
% REFERENCES:
%
%   [Ba15]  B. W. Bader, T. G. Kolda and others. MATLAB Tensor Toolbox 
%           Version 2.6, Available online, February 2015. 
%           URL: http://www.sandia.gov/~tgkolda/TensorToolbox/.
%
%   [Go13]  G. H. Golub, C. F. Van Loan. Matrix Computations. 4th Edition.
%           Johns Hopkins University Press, Baltimore, 2013.

% Create initialize alpha, beta, gamma tensors
alpha_tensor = zeros(2,2,7);
beta_tensor = zeros(2,2,7);
gamma_tensor = zeros(2,2,7);

% 1st rank 1 component
alpha_tensor(1, 1, 1) = 1;
alpha_tensor(2, 2, 1) = 1;
beta_tensor(1, 1, 1) = 1;
beta_tensor(2, 2, 1) = 1;

% 2nd rank 1 component
alpha_tensor(2, [1 2], 2) = [1 1];
beta_tensor(1, 1, 2) = 1;

% 3rd rank 1 component
alpha_tensor(1, 1, 3) = 1;
beta_tensor(1, 2, 3) = 1;
beta_tensor(2, 2, 3) = -1;

% 4th rank 1 component
alpha_tensor(2, 2, 4) = 1;
beta_tensor(2, 1, 4) = 1;
beta_tensor(1, 1, 4) = -1;

% 5th rank 1 component
alpha_tensor(1, [1 2], 5) = [1 1];
beta_tensor(2, 2, 5) = 1;

% 6th rank 1 component
alpha_tensor(2, 1, 6) = 1;
alpha_tensor(1, 1, 6) = -1;
beta_tensor(1, [1 2], 6) = [1 1];

% 7th rank 1 component
alpha_tensor(1, 2, 7) = 1;
alpha_tensor(2, 2, 7) = -1;
beta_tensor(2, [1 2], 7) = [1 1];

% Compute gamma tensor
gamma_tensor(1, 1, [1 4 5 7]) = [1 1 -1 1];
gamma_tensor(1, 2, [3 5]) = [1 1];
gamma_tensor(2, 1, [2 4]) = [1 1];
gamma_tensor(2, 2, [1 2 3 6]) = [1 -1 1 1];

% Compute factor matrices and create tensor
Y = cell(3,1);
Y{1} = double(tenmat(alpha_tensor,3)).';
Y{2} = double(tenmat(beta_tensor,3)).';
temp = double(tenmat(gamma_tensor,3));
Y{3} = temp(:, repmat([1 3], 1, 2) + repelem([0 1], 1, 2)).';

end