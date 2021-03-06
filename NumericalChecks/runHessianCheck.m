% r=randi(50);
% A=randn(r,randi(r));
% b=randn(size(A,1),1);
% f   = @(x) norm( A*x - b )^2/2;
% grad = @(x) A'*(A*x-b);
% hess = @(x0,x) A'*A*x;
% x0 = randn(size(A,2),1);
%%
% m = randi(10);
% n = randi(10);
% %r=randi(min(m,n));
% r = min(m,n);
% A = randn(m,r)*randn(r,n);
% 
% vec = @(x) x(:);
% %matricize u and v
% U = @(x) reshape(x(1:m*r),[m,r]);
% V = @(x) reshape(x(m*r+1:end),[n,r]);
% g = @(x) U(x)*V(x).'-A ;
% f = @(x) .5*norm(g(x),'Fro')^2;
% grad = @(x) [vec(g(x)*V(x));vec(g(x).'*U(x))];
% Huu = @(x0) kron(V(x0)'*V(x0),eye(m));
% Huv = @(x0) kron(V(x0)',U(x0))*boxProduct(eye(n),eye(r)) +kron(eye(r),g(x0));
% Hvu = @(x0) kron(U(x0)',V(x0))*boxProduct(eye(m),eye(r))+kron(eye(r),g(x0)');
% Hvv = @(x0) kron(U(x0)'*U(x0),eye(n));
% H = @(x0) [Huu(x0) Huv(x0);Hvu(x0) Hvv(x0)];
% %this is the function after H(x0) is applied to x, i.e. hess(x,x0) = H(x0)*x
% hess = @(x0,x) [vec(U(x)*V(x0)'*V(x0))+vec(U(x0)*V(x)'*V(x0)+g(x0)*V(x));vec((U(x)*V(x0)')'*U(x0)+g(x0)'*U(x))+vec((U(x0)*V(x)')'*U(x0))];
% x0 = randn(r*(m+n),1);
%% CP factorization
m = 9;
n = m;
l = m;
r = 22;
Z = generate_tensor;
vec = @(x) x(:);
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);
%H = @(x) tensorHessianOptimized(Z,x,U,V,W);
hess = @(x0,x) H(x0)*x;
%hess = @(x0,x) 0.99 * H(x0)*x;
x0 = randn((m+n+l)*r,1);

%HessianCheck(f,grad,hess,x0,1,20,true);

errHist = simpleHessianCheck( grad, hess, x0 , 'hScaling', 1,'hDecrease',100,'plotting',true);
% This looks great to me!

%% Try known function
% f   = @(x) 3*x^4 - 2*x^3 + 5*x^2 - 4*x + 7;
% g   = @(x) 12*x^3 - 6*x^2 + 10*x -4;
% H_true   = @(x) 36*x^2 - 12*x + 10;
% H_false   = @(x) 36*x^2 - 12*x + 9.9;
% 
% 
% A   = randn(5,10); 
% % A   = randn(10,5);  % try both ways
% b = randn(size(A,1),1);
% f   = @(x) norm(A*x-b)^2/2;
% g   = @(x) A'*(A*x-b);
% H_true = @(x0) A'*A;
% H_false= @(x0) .99*A'*A;
% % Taylor series approximations of Hessian via gradient are exact!
% 
% 
% Hess= @(x0,x) H_true(x0)*x;
% % Hess= @(x0,x) H_false(x0)*x;
% 
% x0  = -3;
% x0  = 17;
% 
%  HessianCheck(f,g,Hess,x0,1,10,true);
% 
% errHist = simpleHessianCheck( g, Hess, x0 , 'hScaling', 1e8,'plotting',true);


%% A simple way to check
simpleHessianCheck( g, Hess, x0 , 'hScaling', 1e-2,'hDecrease',100);

%% Try the values for plotting:
% A bit slower, but more foolproof

% errHist = simpleHessianCheck( g, Hess, x0 , 'hScaling', 1e2,'plot',true);

% figure(1); clf;
% hl=loglog( errHist(:,3), errHist(:,1:2), 'linewidth', 2  );
% xlabel('stepsize');
% 
% [mn,ind]    = min( errHist(:,1) );
% xx  = [errHist(ind,3),errHist(1,3)]
% line( xx, (xx/xx(2)).^1*errHist(1,1) ,'linewidth',2,'linestyle','--','color',[0.9290    0.6940    0.1250]);
% 
% [mn,ind]    = min( errHist(:,2) );
% xx  = [errHist(ind,3),errHist(1,3)]
% % line( [errHist(ind,3),errHist(1,3)], [mn,errHist(1,2)] );
% line( xx, (xx/xx(2)).^2*errHist(1,2)  ,'linewidth',2,'linestyle','--','color',[0.4940    0.1840    0.5560]);
% 
% % axis square
% grid on
% legend('Forward diff','Centered diff','1st order','2nd order','location','northwest');
% set(gca,'fontsize',24)
% title('Forward diff should be 1st order; centered diff should be 2nd order');

%% evalPenaltyFcn_SVD

% t = 1;
% R = 1;
% 
% m = randi(20);
% n = randi(20);
% r = min(m,n);
% U = @(x) reshape(x(1:m*r),[m,r]);
% V = @(x) reshape(x(m*r+1:end),[n,r]);
% f = @(x) evalPenaltyFcn(x,t,R,U,V,1);
% grad = @(x) evalPenaltyFcn(x,t,R,U,V,2);
% H = @(x) evalPenaltyFcn(x,t,R,U,V,3);
% hess = @(x0,x) H(x0)*x;
% x0 = randn(r*(m+n),1);
% HessianCheck( f, grad, hess,x0, 1,10,true);
% simpleHessianCheck( grad, hess, x0 , 'hScaling', 1e2,'hDecrease',100,'plotting',false);
%% evalPenaltyFcn_CP

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
H = @(x) tensorHessianOptimized(x,U,V,W);

t=1;
R=100;
f_phi = @(x) f(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,1);
grad_phi = @(x) grad(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,2);
H_phi = @(x) H(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,3);
hess = @(x0,x) H_phi(x0)*x;
%hess = @(x0,x) 0.99*H_phi(x0)*x;
x0 = randn((m+n+l)*r,1);
simpleHessianCheck( grad_phi, hess, x0 , 'hScaling', 1e2,'hDecrease',100,'plotting',true);
