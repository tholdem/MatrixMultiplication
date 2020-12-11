R = 23;
Z = fmt(generate_tensor);

% Compute the CPD of the full tensor T.
options.Display = true; % Show progress on the command line.
options.Initialization = @cpd_rnd; % Select pseudorandom initialization.
options.Algorithm = @cpd_nls; % Select NLS as the main algorithm.
options.AlgorithmOptions.LineSearch = @cpd_els; % Add exact line search.
options.AlgorithmOptions.TolFun = 1e-12; % Set function tolerance stop criterion
options.AlgorithmOptions.TolX   = -1; % Set step size tolerance stop criterion
options.AlgorithmOptions.MaxIter = 500;
options.AlgorithmOptions.CGMaxIter = 500;

[F, output] = cpd(Z,R,options);

semilogy(output.Algorithm.fval);
xlabel('iterations')
ylabel('total error')
