function Y = laderman_decom
% LADERMAN_DECOMP Create the CP tensor corresponding to Laderman's
% decomposition.
%
%   This script requires Tensor Toolbox version 2.6 [Ba15].
%
%   LADERMAN_DECOMP is a script that computes the tensor corresponding to
%   Laderman's rank 23 matrix multiplication algorithm for 3 by 3 matrices
%   [La76]. The tensor is stored in X_strassen. The factor matrices are
%   also stored in the cell Y.
%
% REFERENCES:
%
%   [Ba15]  B. W. Bader, T. G. Kolda and others. MATLAB Tensor Toolbox 
%           Version 2.6, Available online, February 2015. 
%           URL: http://www.sandia.gov/~tgkolda/TensorToolbox/.
%
%   [La76]  J. D. Laderman. A noncommutative algorithm for multiplying 3×3
%           matrices using 23 multiplications. Bulletin of the AMS 82(1),
%           pp. 126-128, 1976.

alpha_tensor = zeros(3,3,23);
beta_tensor = zeros(3,3,23);
gamma_tensor = zeros(3,3,23);

% 1st rank 1 component
alpha_tensor(1, [1 2 3], 1) = [1 1 1];
alpha_tensor(2, [1 2], 1) = [-1 -1];
alpha_tensor(3, [2 3], 1) = [-1 -1];
beta_tensor(2, 2, 1) = 1;

% 2nd rank 1 component
alpha_tensor(1, 1, 2) = 1;
alpha_tensor(2, 1, 2) = -1;
beta_tensor(1, 2, 2) = -1;
beta_tensor(2, 2, 2) = 1;

% 3rd rank 1 component
alpha_tensor(2, 2, 3) = 1;
beta_tensor(1, [1 2], 3) = [-1 1];
beta_tensor(2, [1 2 3], 3) = [1 -1 -1];
beta_tensor(3, [1 3], 3) = [-1 1];

% 4th rank 1 component
alpha_tensor(1, 1, 4) = -1;
alpha_tensor(2, [1 2], 4) = [1 1];
beta_tensor(1, [1 2], 4) = [1 -1];
beta_tensor(2, 2, 4) = 1;

% 5th rank 1 component
alpha_tensor(2, [1 2], 5) = [1 1];
beta_tensor(1, [1 2], 5) = [-1 1];

% 6th rank 1 component
alpha_tensor(1, 1, 6) = 1;
beta_tensor(1, 1, 6) = 1;

% 7th rank 1 component
alpha_tensor(1, 1, 7) = -1;
alpha_tensor(3, [1 2], 7) = [1 1];
beta_tensor(1, [1 3], 7) = [1 -1];
beta_tensor(2, 3, 7) = 1;

% 8th rank 1 component
alpha_tensor(1, 1, 8) = -1;
alpha_tensor(3, 1, 8) = 1;
beta_tensor(1, 3, 8) = 1;
beta_tensor(2, 3, 8) = -1;

% 9th rank 1 component
alpha_tensor(3, [1 2], 9) = [1 1];
beta_tensor(1, [1 3], 9) = [-1 1];

% 10th rank 1 component
alpha_tensor(1, [1 2 3], 10) = [1 1 1];
alpha_tensor(2, [2 3], 10) = [-1 -1];
alpha_tensor(3, [1 2], 10) = [-1 -1];
beta_tensor(2, 3, 10) = 1;

% 11th rank 1 component
alpha_tensor(3, 2, 11) = 1;
beta_tensor(1, [1 3], 11) = [-1 1];
beta_tensor(2, [1 2 3], 11) = [1 -1 -1];
beta_tensor(3, [1 2], 11) = [-1 1];

% 12th rank 1 component
alpha_tensor(1, 3, 12) = -1;
alpha_tensor(3, [2 3], 12) = [1 1];
beta_tensor(2, 2, 12) = 1;
beta_tensor(3, [1 2], 12) = [1 -1];

% 13th rank 1 component
alpha_tensor(1, 3, 13) = 1;
alpha_tensor(3, 3, 13) = -1;
beta_tensor(2, 2, 13) = 1;
beta_tensor(3, 2, 13) = -1;

% 14th rank 1 component
alpha_tensor(1, 3, 14) = 1;
beta_tensor(3, 1, 14) = 1;

% 15th rank 1 component
alpha_tensor(3, [2 3], 15) = [1 1];
beta_tensor(3, [1 2], 15) = [-1 1];

% 16th rank 1 component
alpha_tensor(1, 3, 16) = -1;
alpha_tensor(2, [2 3], 16) = [1 1];
beta_tensor(2, 3, 16) = 1;
beta_tensor(3, [1 3], 16) = [1 -1];

% 17th rank 1 component
alpha_tensor(1, 3, 17) = 1;
alpha_tensor(2, 3, 17) = -1;
beta_tensor(2, 3, 17) = 1;
beta_tensor(3, 3, 17) = -1;

% 18th rank 1 component
alpha_tensor(2, [2 3], 18) = [1 1];
beta_tensor(3, [1 3], 18) = [-1 1];

% 19th rank 1 component
alpha_tensor(1, 2, 19) = 1;
beta_tensor(2, 1, 19) = 1;

% 20th rank 1 component
alpha_tensor(2, 3, 20) = 1;
beta_tensor(3, 2, 20) = 1;

% 21st rank 1 component
alpha_tensor(2, 1, 21) = 1;
beta_tensor(1, 3, 21) = 1;

% 22nd rank 1 component
alpha_tensor(3, 1, 22) = 1;
beta_tensor(1, 2, 22) = 1;

% 23rd rank 1 component
alpha_tensor(3, 3, 23) = 1;
beta_tensor(3, 3, 23) = 1;

gamma_tensor(1, 1, [6 14 19]) = 1;
gamma_tensor(1, 2, [1 4 5 6 12 14 15]) = 1;
gamma_tensor(1, 3, [6 7 9 10 14 16 18]) = 1;
gamma_tensor(2, 1, [2 3 4 6 14 16 17]) = 1;
gamma_tensor(2, 2, [2 4 5 6 20]) = 1;
gamma_tensor(2, 3, [14 16 17 18 21]) = 1;
gamma_tensor(3, 1, [6 7 8 11 12 13 14]) = 1;
gamma_tensor(3, 2, [12 13 14 15 22]) = 1;
gamma_tensor(3, 3, [6 7 8 9 23]) = 1;

%% Compute factor matrices

Y = cell(3,1);

Y{1} = double(tenmat(alpha_tensor,3)).';
Y{2} = double(tenmat(beta_tensor,3)).';
temp = double(tenmat(gamma_tensor,3));
Y{3} = temp(:, repmat([1 4 7], 1, 3) + repelem([0 1 2], 1, 3)).';

% X_laderman = tensor(ktensor(Y));