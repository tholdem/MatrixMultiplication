function HM = tensorHessian(Z,x,U,V,W)
%implementation of Theorem 4.3 of Sandia 200num_row Tech Report
%Z is the tensor representing 3 by 3 matrix multiplication
%U,V,W are matricization functions for the factor matrices
for k = 1:10
tic
Ux = U(x);
Vx = V(x);
Wx = W(x);
num_row = size(Ux,1);
rank = size(Ux,2);
G = @(A,B) A.'*A.*(B.'*B);
%each cell is the elementwise product of the Gram matrices of factor
%matrices except for the factor matrix of cell index, also known as nth Gamma
Gamma = {G(Vx,Wx),G(Ux,Wx),G(Ux,Vx)};
X = {Ux,Vx,Wx};
H = cell(rank*3,rank*3);

%when n(matrix) is the same but r (columns) are different
%block diagonal matrices on the diagonal of H
for n = 1:3
    Gamma_n = cell2mat(Gamma(n));
    for s = 1:rank
        for r = 1:rank
            H(r+rank*(n-1),s+rank*(n-1)) = {Gamma_n(r,s)*eye(num_row)};
        end
    end
end
%for the next two cases we only find  the upper triangle part to avoid
%error
% for k=1:10
% tic
%when n are different and r is the same
for n = 1:3
    for p = n+1:3
        An = cell2mat(X(n));
        Ap = cell2mat(X(p));
        for r = 1:rank
            term1 = zeros(num_row,num_row);
            term3 = zeros(num_row,num_row);
            %different cases of remaining matrix and term1, term3.
            if n==1 && p==2
                %remaining matrix
                Rx = Wx;
                %term1 is I1 by I2 matrix, i is i1, j is i2
                for i = 1:num_row
                    for j = 1:num_row
                         term1(i,j) = reshape(Z(i,j,:),[num_row,1]).' * Rx(:,r);
                    end
                end
                %psi_rl is the inner product of rth,lth col of remaining matrix
                %combine half of 2nd term and 3rd term for simplicity 
                for l = 1:rank %this is lower case of L, not 1!
                    term3 = term3 + Rx(:,r).'*Rx(:,l)*An(:,l)*Ap(:,l).';
                end
            elseif n==1 && p==3
                Rx = Vx;
                for i = 1:num_row
                    for j = 1:num_row
                         term1(i,j) = reshape(Z(i,:,j),[num_row,1]).' * Rx(:,r);
                    end
                end
                for l = 1:rank
                    term3 = term3 + Rx(:,r).'*Rx(:,l)*An(:,l)*Ap(:,l).';
                end
            elseif n==2 && p==3
                Rx = Ux;
                for i = 1:num_row
                    for j = 1:num_row
                         term1(i,j) = reshape(Z(:,i,j),[num_row,1]).' * Rx(:,r);
                    end
                end
                for l = 1:rank
                    term3 = term3 + Rx(:,r).'*Rx(:,l)*An(:,l)*Ap(:,l).';
                end
            else
                fprintf('Something wrong with the 2nd loop! n=%f,p=%f.\n',n,p);
            end
            %term2 = Rx(:,r).'*Rx(:,r)*An(:,r)*Ap(:,r).'
            %each term is a nxn matrix, where n is num_row
            H(r+rank*(n-1),r+rank*(p-1)) = { -term1 + Rx(:,r).'*Rx(:,r)*An(:,r)*Ap(:,r).' + term3};            
        end
    end
end
% toc
% end
% for k=1:10
% tic
%both n and r are different
for n = 1:3
    for p = n+1:3
        An = cell2mat(X(n));
        Ap = cell2mat(X(p));
        if n==1 && p==2
            Rx = Wx;
        elseif n==1 && p==3
            Rx = Vx;
        elseif n==2 && p==3
            Rx = Ux;
        else
            fprintf('Something wrong with the 2nd loop! n=%f,p=%f.\n',n,p);
        end
        for r = 1:rank
            for s = r+1:rank
                %psi_rs is the inner product of rth,sth col of remaining matrix
                H(r+rank*(n-1),s+rank*(p-1)) = {Rx(:,r).'*Rx(:,s)*An(:,s)*Ap(:,r).'};
                H(s+rank*(n-1),r+rank*(p-1)) = {Rx(:,s).'*Rx(:,r)*An(:,r)*Ap(:,s).'};
            end
        end
    end
end
% toc
% end
%# find empty cells
emptyCells = cellfun(@isempty,H);
%# insert nxn zeros in each empty cell for cell2mat
H(emptyCells) = {zeros(num_row)};
HM = cell2mat(H);
HM = triu(HM)+triu(HM,1).';
toc
end
end