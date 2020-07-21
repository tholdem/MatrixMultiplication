function outputFcn = evalPenaltyFcn_CP(x,t,R,U,V,W,i) %#codegen
%Usage: [phi,phi_grad,phi_H] = evalPenaltyFcn(x,t,R,U,V,W,i)
%as t decreases, the penalty gets larger
%R is the radius of the spheres we constrain the columns in 
%U,V,W are matricization functions
%i is the index of output function. 1=f,2=grad,3=H.
Ux = U(x);
Vx = V(x);
Wx = W(x);
r = size(Ux,2);

if i==1
    %phi, if norm(column)>=R, this sum increases
    outputFcn = 1/t*(sum(max(0,sum(Ux.^2,1)-R^2))+sum(max(0,sum(Vx.^2,1)-R^2))+sum(max(0,sum(Wx.^2,1)-R^2)));
    if outputFcn~=0
        fprintf('Penalty activated.\n')
    end
    return
elseif i==2
    phi_gradU = zeros(size(Ux));
    phi_gradV = zeros(size(Vx));
    phi_gradW = zeros(size(Wx));
    %going through each column since they are separable in differentiation
    for j=1:r
        if norm(Ux(:,j)) >= R
            %fill the gradient of column at the right location in gradient of x
            phi_gradU(:,j)  = 2/t*Ux(:,j); % easier bookkeeping
        end
    end
    for j=1:r
        if norm(Vx(:,j)) >= R
            phi_gradV(:,j)  = 2/t*Vx(:,j);
        end
    end
    for j=1:r
        if norm(Wx(:,j)) >= R
            phi_gradW(:,j)  = 2/t*Wx(:,j);
        end
    end
    outputFcn = [ phi_gradU(:) ; phi_gradV(:); phi_gradW(:) ]; % easier bookkeping
    return
elseif i==3
    phi_HU = zeros(size(Ux));
    phi_HV = zeros(size(Vx));
    phi_HW = zeros(size(Wx));
    for j=1:r
        if norm(Ux(:,j)) >= R
            %fill the Hessian of column for its corresponding diagonal spots in
            %Hessian of x
            phi_HU(:,j) = 2/t; 
        end
    end
    for j=1:r
        if norm(Vx(:,j)) >= R
            phi_HV(:,j) = 2/t;  
        end
    end
    for j=1:r
        if norm(Wx(:,j)) >= R
            phi_HW(:,j) = 2/t;  
        end
    end
    outputFcn = diag([ phi_HU(:) ; phi_HV(:); phi_HW(:)]);
    return
end

end
% %log-barrier function and derivatives
% c = m+n; %number of functions in the sum, which is the total number of columns in U and V
% phi = @(x,t) -1/t*(sum(log(-(sum(U(x).^2,1)-1)))+ sum(log(-(sum(V(x).^2,1)-1))));
% phi_grad = @(x,t) -2*[vec(U(x)*diag(1./(sum(U(x).^2,1)-1))); vec(V(x)*diag(1./(sum(V(x).^2,1)-1)))];