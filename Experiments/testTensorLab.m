R = 23;
Z = fmt(generate_tensor);

% Compute the CPD of the full tensor T.
options.Display = true; % Show progress on the command line.
options.Initialization = @cpd_rnd; % Select pseudorandom initialization.
options.Algorithm = @cpd_nls; % Select NLS as the main algorithm.
options.AlgorithmOptions.LineSearch = @cpd_els; % Add exact line search.
options.AlgorithmOptions.TolFun = 1e-12; % Set function tolerance stop criterion
options.AlgorithmOptions.TolX   = 1e-12; % Set step size tolerance stop criterion
options.AlgorithmOptions.MaxIter = 1e4;
options.AlgorithmOptions.CGMaxIter = 1e3;

[F, output] = cpd(Z,R,options);

semilogy(output.Algorithm.fval);
xlabel('iterations')
ylabel('total error')

rankest(Z);
cpd_gevd(Z,R)