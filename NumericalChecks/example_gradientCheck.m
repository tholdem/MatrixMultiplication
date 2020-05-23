%{
This is an example using a correct gradient to see what
the output of gradientCheck.m should look like

-Stephen
%}

rng(0);
%n   = 10; % be careful: if n is large, default behavior changes
 n   = 100;
A   = randn(n);
b   = randn(n,1);
f   = @(x) norm( A*x - b )^2/2;
%gra = @(x) A'*(A*x-b);
 gra = @(x) A'*(A*x-b); % wrong gradient

x0  = randn(n,1);


gradientCheck( f, gra, x0 ); % defaults
%%

scaling = 1e0;
numberPoints = 5;
gradientCheck( f, gra, x0 )

%% if n is large, it won't do "forward diff" and "central diff" by default
% (since these form the entire n-dimensional gradient)
% so if you want these, turn "FORCE_FINITE_DIFF" to true

scaling = 1e-3
numberPoints    = 20;
FORCE_FINITE_DIFF = true;
gradientCheck( f, gra, x0, scaling, numberPoints, FORCE_FINITE_DIFF );

%% 2020
%{
Todo:
  For large dimensions, when finding the entire forward/centra diff
gradient is slow, use a randomized estimator (along SSD lines)

%}