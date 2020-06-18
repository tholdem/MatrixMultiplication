function HM = tensorHessian(Z,x,U,V,W)
%Z is the tensor representing 3 by 3 matrix multiplication
%U,V,W are matricization functions for the factor matrices
Ux = U(x);
Vx = V(x);
Wx = W(x);
G = @(A,B) A.'*A.*(B.'*B);
%each cell is the elementwise product of the Gram matrices of factor
%matrices except for the factor matrix of cell index, also known as nth Gamma
Gamma = {G(Vx,Wx),G(Ux,Wx),G(Ux,Vx)};
X = {Ux,Vx,Wx};
rank = size(Ux,2);
H = cell(rank*3,rank*3);


%when n(matrix) is the same but r (columns) are different
%block diagonal matrices on the diagonal of H
for n = 1:3
    Gamma_n = cell2mat(Gamma(n));
    for r = 1:rank
        for s = 1:rank
            H(r+rank*(n-1),s+rank*(n-1)) = {Gamma_n(r,s)*eye(9)};
        end
    end
end

%when n are different and r is the same
for n = 1:3
    for p = n+1:3
        for r = 1:rank
            An = cell2mat(X(n));
            Ap = cell2mat(X(p));
            term3 = zeros(9,9);
            if n==1 && p==2
                %remaining matrix
                Rx = Wx;
                %psi_rl is the inner product of rth,lth col of remaining matrix
                %combine half of 2nd term and 3rd term for simplicity 
                for l = 1:rank
                    term3 = term3 + Rx(:,r).'*Rx(:,l)*An(:,l)*Ap(:,l).';
                end
                H(r+rank*(n-1),r+rank*(p-1)) = {-reshape(Z(n,p,:),[9,1]).' * Rx(:,r) + Rx(:,r).'*Rx(:,r)*An(:,r)*Ap(:,r).' + term3};
            elseif n==1 && p==3
                Rx = Vx;
                for l = 1:rank
                    term3 = term3 + Rx(:,r).'*Rx(:,l)*An(:,l)*Ap(:,l).';
                end
                H(r+rank*(n-1),r+rank*(p-1)) = {-reshape(Z(n,:,p),[9,1]).' * Rx(:,r) + Rx(:,r).'*Rx(:,r)*An(:,r)*Ap(:,r).' + term3};
            elseif n==2 && p==3
                Rx = Ux;
                for l = 1:rank
                    term3 = term3 + Rx(:,r).'*Rx(:,l)*An(:,l)*Ap(:,l).';
                end
                H(r+rank*(n-1),r+rank*(p-1)) = {-reshape(Z(:,n,p),[9,1]).' * Rx(:,r) + Rx(:,r).'*Rx(:,r)*An(:,r)*Ap(:,r).' + term3};
            else
                fprintf('Something wrong with the 2nd loop! n=%f,p=%f.\n',n,p);
            end
            H(r+rank*(p-1),r+rank*(n-1)) = H(r+rank*(n-1),r+rank*(p-1));
        end
    end
end
%both n and r are different
for n = 1:3
    for p = n+1:3
        for r = 1:rank
            for s = r+1:rank
                An = cell2mat(X(n));
                Ap = cell2mat(X(p));
                if n==1 && p==2
                    Rx = Wx;
                elseif n==1 && p==3
                    Rx = Vx;
                elseif n==2 && p==3
                    Rx = Ux;
                else
                    fprintf('Something wrong with the 3rd loop! n=%f,p=%f.\n',n,p);
                end
                %psi_rs is the inner product of rth,sth col of remaining matrix
                H(r+rank*(n-1),s+rank*(p-1)) = {Rx(:,r).'*Rx(:,s)*An(:,s)*Ap(:,r).'};
                H(s+rank*(p-1),r+rank*(n-1)) = H(r+rank*(n-1),s+rank*(p-1));
                H(s+rank*(n-1),r+rank*(p-1)) = {Rx(:,s).'*Rx(:,r)*An(:,r)*Ap(:,s).'};
                H(r+rank*(p-1),s+rank*(n-1)) = H(s+rank*(n-1),r+rank*(p-1));
            end
        end
    end
end

HM = cell2mat(H);