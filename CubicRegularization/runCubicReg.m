%this is the current correct way to use cubicReg:
[x,errorHistory] = cubicReg(f,grad,'errTol',1e-12,'maxIts',1e3,'x0',x0,'kappa_easy',1e-4,'errFcn',errFcn,'Hessian',H);
%if time is not a concern you can use smaller kappa_easy which determines
%how accurate the subproblem solution is but is expensive
%you can adjust sigma, eta1, and eta2 if you want, but the default should
%work just fine



%%
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
% [x,errorHistory] = cubicReg(F,Grad,'errTol',1e-6,'maxIts',1e5,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',Hess,'normalize','on','normalFcn',N);

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
% [x,errorHistory] = cubicReg(f,grad,'errTol',1e-6,'maxIts',1e3,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H,'projection','off','projFcn',Proj);
% %passed!
% 
% %sanity check 2 using norm(M)>>
% [UU,DD,VV] = svd(A,'econ');
% UU = UU*DD;
% M = 100*randn(r,r);
% UU = UU*M;
% VV = VV/M.';
% x0 = [UU(:);VV(:)];
% [x,errorHistory] = cubicReg(f,grad,'errTol',1e-6,'maxIts',1e3,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H,'projection','off','projFcn',Proj);
% %passed!
% 
% %now with penalty
% [x,errorHistory] = cubicReg(f_phi,grad_phi,'errTol',1e-6,'maxIts',1e2,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H_phi,'projection','off','projFcn',Proj,'penalty','on');
% %passed!
%%
%CP factorization
m = 9;
n = 9;
l = 9;
rlist = [27,23,22];
rlist = [23,22];

Z = generate_tensor;
maxIts=500;
errTol=1e-12;
N=1000;
for r = rlist
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);

% % force columns of U and V to be
% PU = @(x) U(x)/max(10,sqrt(max(sum(U(x).^2,1))));
% PV = @(x) V(x)/max(10,sqrt(max(sum(V(x).^2,1))));
% PW = @(x) W(x)/max(10,sqrt(max(sum(W(x).^2,1))));
% Proj = @(x) [vec(PU(x));vec(PV(x));vec(PW(x))];

% t=5;
% R=5;
% f_phi = @(x) f(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,1);
% grad_phi = @(x) grad(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,2);
% H_phi = @(x) H(x) + evalPenaltyFcn_CP(x,t,R,U,V,W,3);

errFcn = f;

x0=zeros((m+n+l)*r,N);
x=x0;
errorHistory = zeros(maxIts+1,N);
Out = cell(N,1);
for i=1:N
    rng(i);
    x0(:,i) =  0.1*randn((m+n+l)*r,1);
    %%
    %[x,errorHistory] = cubicReg(f,grad,'errTol',1e-8,'maxIts',1e2,'x0',x0,'errFcn',errFcn,'iterInterval',20,'method','adaptive','Hessian',H,'projection','on','projFcn',Proj);
    [x(:,i),out] = cubicReg(f,grad,'errTol',errTol,'maxIts',maxIts,'x0',x0(:,i),'kappa_easy',1e-4,'errFcn',errFcn,'Hessian',H);
    errorHistory(:,i) = out.errHistory;
    Out(i) = {out};
    % figure;
    % semilogy(errorHistory);
    % xlabel('iterations')
    % ylabel('total error')
end
% [x,errorHistory] = Copy_of_cubicReg(f_phi,grad_phi,'errTol',1e-6,'maxIts',1e3,'x0',x0,'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H_phi,'penalty','off');
% [x,errorHistory] = cubicReg(f_phi,grad_phi,'errTol',1e-12,'maxIts',1e3,'x0',x0,'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H_phi);
% [x,errorHistory] = cubicReg4Coder(f,grad,H,x0,errFcn,errTol,maxIts);
fig=figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' Euclidean ARC'])
xlabel('iterations')
xlim([1 maxIts+1])
ylabel('Objective function value')
ylim([errTol/10 1e2])

saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\ARC_' num2str(r) '_fval.fig'])
saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\ARC_' num2str(r) '_fval.png'])
save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat'],'x0','x','errorHistory','Out');
end

%% append more iterations

m = 9;
n = 9;
l = 9;
rlist = [27,23,22];
Z = generate_tensor;
maxIts=100;
pastIts=100;
errTol=1e-12;
N=2;
for r = rlist
%matricize u, v, w
U = @(x) reshape(x(1:m*r),[m,r]);
V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
f = @(x) func_f(Z,x,U,V,W);
grad = @(x) grad_f(Z,x,U,V,W);
H = @(x) tensorHessianOptimized(x,U,V,W);

errFcn = f;

past = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat']);
x0=past.x;
x=zeros(size(x0));
errorHistory1 = zeros(maxIts,N);
for i=1:N
    if past.errorHistory(end) < errTol
        continue
    else
        [x(:,i),errorHistory1(:,i)] = cubicReg(f,grad,'errTol',errTol,'maxIts',maxIts,'x0',x0(:,i),'kappa_easy',1e-3,'errFcn',errFcn,'Hessian',H);
    end
end
errorHistory=[past.errorHistory;errorHistory1];
fig=figure;
semilogy(errorHistory);
title(['Rank ' num2str(r) ' Euclidean ARC'])
xlabel('iterations')
xlim([1 pastIts+maxIts+1])
ylabel('Objective function value')
ylim([errTol/10 1e2])

saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\ARC_' num2str(r) '_fval.fig'])
save(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat'],'x0','x','errorHistory');
end