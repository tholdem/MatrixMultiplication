function outputFcn = evalPenaltyFcn_SVD(x,t,R,U,V,i)
%Usage: [phi,phi_grad,phi_H] = evalPenaltyFcn(x,t,R,U,V,i)
%as t decreases, the penalty gets larger
%R is the radius of the spheres we constrain the columns in 
%U,V are matricization functions
%i is the index of output function. 1=f,2=grad,3=H.
Ux = U(x);
Vx = V(x);
%if norm(column)>=R, this sum increases
phi = 1/t*(sum(max(0,sum(Ux.^2,1)-R^2))+sum(max(0,sum(Vx.^2,1)-R^2)));
% phi_grad = zeros(size(x));
phi_gradU = zeros(size(Ux));
phi_gradV = zeros(size(Vx));
phi_HU = zeros(size(Ux));
phi_HV = zeros(size(Vx));

r = size(Ux,2);

%going through each column since they are separable in differentiation
for j=1:r
    if norm(Ux(:,j)) >= R
        %fill the gradient of column at the right location in gradient of x
%         phi_grad((j-1)*m+1:j*m) =  2/t*Ux(:,j);
        
        phi_gradU(:,j)  = 2/t*Ux(:,j); % easier bookkeeping
        
        %fill the Hessian of column for its corresponding diagonal spots in
        %Hessian of x
        phi_HU(:,j) = 2/t; 
    end
end
for j=1:r
    if norm(Vx(:,j)) >= R
%         phi_grad((j-1)*n+1:j*n) = 2/t*Vx(:,j);
        phi_gradV(:,j)  = 2/t*Vx(:,j);
        phi_HV(:,j) = 2/t;  
    end
end
phi_grad = [ phi_gradU(:) ; phi_gradV(:) ]; % easier bookkeping
phi_H = diag([ phi_HU(:) ; phi_HV(:) ]);
%we can choose which to output for building anonymous function
fcns = {phi,phi_grad,phi_H};
outputFcn = cell2mat(fcns(i));
end
% %log-barrier function and derivatives
% c = m+n; %number of functions in the sum, which is the total number of columns in U and V
% phi = @(x,t) -1/t*(sum(log(-(sum(U(x).^2,1)-1)))+ sum(log(-(sum(V(x).^2,1)-1))));
% phi_grad = @(x,t) -2*[vec(U(x)*diag(1./(sum(U(x).^2,1)-1))); vec(V(x)*diag(1./(sum(V(x).^2,1)-1)))];