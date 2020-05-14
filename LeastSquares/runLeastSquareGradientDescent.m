r=randi(1000);
A=10*rand(r,randi(r));
b=10*rand(size(A,1),1);
x_star = (A.'*A)\A.'*b;
errFcn  = @(x) norm( x - x_star )/norm( x_star );
f       = @(x) 1/2*norm(A*x-b)^2; % on this line, 'x' is a dummy variable
gradient= @(x) A'*(A*x-b);

[x,errorHistory] = gradientDescent(f,gradient,'errorThd',1e-15,'maxIts',1e5,'initialPoint',randn(size(A,2),1),'algo','leastsquares','matrix',A,'errFcn',errFcn);
semilogy(errorHistory);
xlabel('iterations')
ylabel('total error')