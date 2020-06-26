%least squares (convex, constant Hessian)
% r=10;
% A=randn(r,randi(r));
% b=randn(size(A,1),1);
% f   = @(x) norm( A*x - b )^2/2;
% grad = @(x) A'*(A*x-b);
% Hess = @(x0,x) A'*A*x;
% H = @(x) A'*A;
% x0 = randn(size(A,2),1);
% x_star = A\b;
% errFcn=@(x) norm( x - x_star )/norm( x_star );

%%
% %logistic regression (convex, Lipschitz Hessian?) See HW5
% p = 5;
% n = 100;
% y = randn(n,1);
% y = -(y>0)+(y<0);
% y_cat = categorical(y);
% X = randn(p,n);
% f = @(w) sum(log(1+exp(-y.*(w.'*X).')));
% sigma = @(a) 1./(1+exp(-a));
% mu = @(w) sigma(y.*(w.'*X).');
% grad = @(w) -X*(y.*(1-mu(w)));
% S = @(w) diag(mu(w).*(1-mu(w)));
% H = @(w) X*S(w)*X.';
% Hess = @(x0,x) X*S(x0)*X.'*x;
% 
% x0 = randn(p,1);
% gradientCheck(f,grad,x0);
% HessianCheck(f,grad,Hess,x0);

% %the sign is negative for some reason, most likely a label disparity
% x_star = mnrfit(X.',y_cat);
% x_star = -x_star(2:end);
% errFcn=@(x) norm( x - x_star )/norm( x_star );

%%
%simple 2D domain function (nonconvex, bounded Hessian)
% f  = @(X,Y) 1/2*(X.^2 - Y.^2);
% 
% % make this only a local function: multiply by Gaussian "g"
% % (otherwise, it has no minimizers)
% sigma2  = .2;
% g       = @(X,Y) exp( -(X.^2+Y.^2)/sigma2 );
% 
% % The function we are interested in is h=f*g
% h       = @(X,Y) f(X,Y).*g(X,Y);
% 
% % Find partial derivatives (w.r.t. x and then y)
% h_x  = @(X,Y) X.*g(X,Y) - 1/sigma2*(X.^2-Y.^2).*X.*g(X,Y);
% h_y  = @(X,Y) -Y.*g(X,Y) - 1/sigma2*(X.^2-Y.^2).*Y.*g(X,Y);
% 
% % Make Hessian
% h_xx = @(X,Y) 2*X.^4 + sigma2*(Y.^2+sigma2)-X.^2*(2*Y.^2+5*sigma2);
% h_xy = @(X,Y) 2*X.*Y.*(X.^2-Y.^2);
% h_yx = @(X,Y) h_xy(X,Y);
% h_yy = @(X,Y) -2*Y.^4+sigma2*Y.^2*sigma2-sigma2^2+X.^2.*( 2*Y.^2-sigma2);
% hess = @(X,Y) g(X,Y)/(sigma2^2).*[ h_xx(X,Y), h_xy(X,Y); h_yx(X,Y), h_yy(X,Y) ];
% 
% % Make versions of the functions that take in xvec=[x;y]
% F       = @(xvec) h(xvec(1),xvec(2));
% Grad    = @(xvec) [h_x( xvec(1), xvec(2) ); h_y( xvec(1), xvec(2) ) ];
% Hess    = @(xvec) hess( xvec(1), xvec(2) );
% 
% %normalizing function
% N = @(x) x/max(1,max(abs(x)));
% 
% x0 = randn(2,1);
% errFcn = @(x) min(norm(x - [0;-.447213595499958]),norm(x - [0;.447213595499958]));
% [x,errorHistory] = cubicReg(F,Grad,'errThd',1e-6,'maxIts',1e5,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',Hess,'normalize','on','normalFcn',N);

%%
% %SVD (nonconvex, unbounded Hessian)
% m = randi(20);
% n = randi(20);
% %r=randi(min(m,n));
% r = min(m,n);
% A = randn(m,r)*randn(r,n);
% [P,~,Q] = svd(A,'econ');
% %projection matrices to column spaces of true P and Q
% P = P/(P.'*P)*P.';
% Q = Q/(Q.'*Q)*Q.';
% 
% vec = @(x) x(:);
% %matricize u and v
% U = @(x) reshape(x(1:m*r),[m,r]);
% V = @(x) reshape(x(m*r+1:end),[n,r]);
% % force columns of U and V to be
% PU = @(x) U(x)/max(1,sqrt(max(sum(U(x).^2,1))));
% PV = @(x) V(x)/max(1,sqrt(max(sum(V(x).^2,1))));
% Proj = @(x) [vec(PU(x));vec(PV(x))];
% %check for numerical errors in difference, no problem
% %d = @(x,y) 0.5*(norm(U(x)*V(x).','Fro')^2-norm(U(y)*V(y).','Fro')^2 - 2*sum(dot(U(x)*V(x).'-U(y)*V(y).',A)));
% 
% g = @(x) U(x)*V(x).'-A ;
% %objective function
% f = @(x) .5*norm(g(x),'Fro')^2;
% grad = @(x) [vec(g(x)*V(x));vec(g(x).'*U(x))];
% %implicit Hessian
% hess = @(x0,x) [vec(U(x)*V(x0)'*V(x0))+vec(U(x0)*V(x)'*V(x0)+g(x0)*V(x));vec((U(x)*V(x0)')'*U(x0)+g(x0)'*U(x))+vec((U(x0)*V(x)')'*U(x0))];
% 
% %explicit Hessian
% Huu = @(x0) kron(V(x0)'*V(x0),eye(m));
% Huv = @(x0) kron(V(x0)',U(x0))*boxProduct(eye(n),eye(r)) +kron(eye(r),g(x0));
% Hvu = @(x0) kron(U(x0)',V(x0))*boxProduct(eye(m),eye(r))+kron(eye(r),g(x0)');
% Hvv = @(x0) kron(U(x0)'*U(x0),eye(n));
% H = @(x0) [Huu(x0) Huv(x0);Hvu(x0) Hvv(x0)];
% 
% %see difference between computed U,V and their projections to true U,V's
% %column spaces
% errFcn = @(x) norm(U(x)-P*U(x))+norm(V(x)-Q*V(x));
% x0 = randn((m+n)*r,1);
%%
% %with penalty
% t = 1;
% R = 10;
% f_phi = @(x) f(x) + evalPenaltyFcn(x,t,R,U,V,1);
% grad_phi = @(x) grad(x) + evalPenaltyFcn(x,t,R,U,V,2);
% H_phi = @(x) H(x) + evalPenaltyFcn(x,t,R,U,V,3);
%%
% %sanity check using optimal solution
% [UU,DD,VV] = svd(A,'econ');
% UU = UU*DD;
% x0 = [UU(:);VV(:)];
% [x,errorHistory] = cubicReg(f,grad,'errThd',1e-6,'maxIts',1e3,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H,'projection','off','projFcn',Proj);
% %passed!
% 
% %sanity check 2 using norm(M)>>
% [UU,DD,VV] = svd(A,'econ');
% UU = UU*DD;
% M = 100*randn(r,r);
% UU = UU*M;
% VV = VV/M.';
% x0 = [UU(:);VV(:)];
% [x,errorHistory] = cubicReg(f,grad,'errThd',1e-6,'maxIts',1e3,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H,'projection','off','projFcn',Proj);
% %passed!
% 
% %now with penalty
% [x,errorHistory] = cubicReg(f_phi,grad_phi,'errThd',1e-6,'maxIts',1e2,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H_phi,'projection','off','projFcn',Proj,'penalty','on');
% %passed!
%%
%CP factorization
m = 9;
n = m;
l = m;
r = 22;
Z = generate_tensor;
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessian(Z,x,U,V,W);

% force columns of U and V to be
PU = @(x) U(x)/max(10,sqrt(max(sum(U(x).^2,1))));
PV = @(x) V(x)/max(10,sqrt(max(sum(V(x).^2,1))));
PW = @(x) W(x)/max(10,sqrt(max(sum(W(x).^2,1))));
Proj = @(x) [vec(PU(x));vec(PV(x));vec(PW(x))];

t=5;
R=100;
f_phi = @(x) f(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,1);
grad_phi = @(x) grad(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,2);
H_phi = @(x) H(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,3);

errFcn = @(x) f(x);
x0 = 0.1* randn((m+n+l)*r,1);
%%
%[x,errorHistory] = cubicReg(f,grad,'errThd',1e-8,'maxIts',1e2,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H,'projection','on','projFcn',Proj);
[x,errorHistory] = cubicReg(f_phi,grad_phi,'errThd',1e-5,'maxIts',1e4,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H_phi,'penalty','on');

semilogy(errorHistory);
xlabel('iterations')
ylabel('total error')

