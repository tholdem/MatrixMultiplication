function H = tensorHessianOptimized(Z,x,U,V,W)
%removed cell arrays to save time
%implementation of Theorem 4.3 of Sandia 200dim1 Tech Report
%Z is the tensor representing 3 by 3 matrix multiplication
%U,V,W are matricization functions for the factor matrices
% for k = 1:10
% tic
Ux = U(x);
Vx = V(x);
Wx = W(x);
dim1 = size(Ux,1);
dim2 = dim1;
dim3 = dim1;
rank = size(Ux,2);
G = @(A,B) A.'*A.*(B.'*B);
%each cell is the elementwise product of the Gram matrices of factor
%matrices except for the factor matrix of cell index, also known as nth Gamma
Gamma = cat(3,G(Vx,Wx),G(Ux,Wx),G(Ux,Vx));
X = cat(3,Ux,Vx,Wx);
H = zeros(rank*3*dim1,rank*3*dim1);

%when n(matrix) is the same but r (columns) are different
%block diagonal matrices on the diagonal of H
%accomplished by expanding each entry of Gamma to 9 by 9 diagnal using
%kronecker product
%upper triangle to save computation
%saved 1/3 time
for n = 1:3
   H1 = kron(triu(Gamma(:,:,n)),eye(dim1));
   H(1+(n-1)*size(H1,1):n*size(H1,1),1+(n-1)*size(H1,1):n*size(H1,1))=H1;
end
%for the next two cases we only find the upper triangle part to avoid error

%when n are different and r is the same
for r = 1:rank
    %case 1
    n=1;
    p=2;
    An = X(:,:,n);
    Ap = X(:,:,p);
    term1 = zeros(dim1,dim2);
    term3 = zeros(dim1,dim2,rank);        
    %remaining matrix's rth column
    col_r = Wx(:,r);
    %term1 is I1 by I2 matrix, i is i1, j is i2
    %term1 = ttv(Z,col_r,3); equivalent but slower
    for i = 1:dim1
       term1(i,:) = reshape(Z(i,:,:),[dim2,dim3]) * col_r;
    end              
    %psi_rl is the inner product of rth,lth col of remaining matrix
    %combine half of 2nd term and 3rd term for simplicity                
    for ii = 1:rank 
       term3(:,:,ii) = col_r.'*Wx(:,ii)*An(:,ii)*Ap(:,ii).';
    end
    H((r+rank*(n-1)-1)*dim1+1:(r+rank*(n-1))*dim1,(r+rank*(p-1)-1)*dim1+1:(r+rank*(p-1))*dim1) = -term1 + col_r.'*col_r*An(:,r)*Ap(:,r).' + sum(term3,3);
    %case 2
    %n=1;
    p=3;
    Ap = X(:,:,p);
    col_r = Vx(:,r);
    for j = 1:dim3
       term1(:,j) = reshape(Z(:,:,j),[dim1,dim2]) * col_r;
    end                
    for ii = 1:rank
       term3(:,:,ii) = col_r.'*Vx(:,ii)*An(:,ii)*Ap(:,ii).';
    end
    H((r+rank*(n-1)-1)*dim1+1:(r+rank*(n-1))*dim1,(r+rank*(p-1)-1)*dim1+1:(r+rank*(p-1))*dim1) = -term1 + col_r.'*col_r*An(:,r)*Ap(:,r).' + sum(term3,3);
	%case 3
    n=2;
    %p=3;
    An = X(:,:,n);
    col_r = Ux(:,r);
    for j = 1:dim3
       term1(:,j) =  col_r.' * reshape(Z(:,:,j),[dim1,dim2]);
    end
    for ii = 1:rank
       term3(:,:,ii) = col_r.'*Ux(:,ii)*An(:,ii)*Ap(:,ii).'; 
    end
    %term2 = col_r.'*col_r*An(:,r)*Ap(:,r).'
    %each term is a nxn matrix, where n is dim1
    H((r+rank*(n-1)-1)*dim1+1:(r+rank*(n-1))*dim1,(r+rank*(p-1)-1)*dim1+1:(r+rank*(p-1))*dim1) = -term1 + col_r.'*col_r*An(:,r)*Ap(:,r).' + sum(term3,3);
end

%both n/p and r/s pairs are different
for r = 1:rank
    for s = r+1:rank
        n=1;
        p=2;
        An = X(:,:,n);
        Ap = X(:,:,p);
        H((r+rank*(n-1)-1)*dim1+1:(r+rank*(n-1))*dim1,(s+rank*(p-1)-1)*dim1+1:(s+rank*(p-1))*dim1) = Wx(:,r).'*Wx(:,s)*An(:,s)*Ap(:,r).';
        H((s+rank*(n-1)-1)*dim1+1:(s+rank*(n-1))*dim1,(r+rank*(p-1)-1)*dim1+1:(r+rank*(p-1))*dim1) = Wx(:,s).'*Wx(:,r)*An(:,r)*Ap(:,s).';
        p=3;
        Ap = X(:,:,p);        
        H((r+rank*(n-1)-1)*dim1+1:(r+rank*(n-1))*dim1,(s+rank*(p-1)-1)*dim1+1:(s+rank*(p-1))*dim1) = Vx(:,r).'*Vx(:,s)*An(:,s)*Ap(:,r).';
        H((s+rank*(n-1)-1)*dim1+1:(s+rank*(n-1))*dim1,(r+rank*(p-1)-1)*dim1+1:(r+rank*(p-1))*dim1) = Vx(:,s).'*Vx(:,r)*An(:,r)*Ap(:,s).';
        n=2;
        An = X(:,:,n);
        %psi_rs is the inner product of rth,sth col of remaining matrix
        H((r+rank*(n-1)-1)*dim1+1:(r+rank*(n-1))*dim1,(s+rank*(p-1)-1)*dim1+1:(s+rank*(p-1))*dim1) = Ux(:,r).'*Ux(:,s)*An(:,s)*Ap(:,r).';
        H((s+rank*(n-1)-1)*dim1+1:(s+rank*(n-1))*dim1,(r+rank*(p-1)-1)*dim1+1:(r+rank*(p-1))*dim1) = Ux(:,s).'*Ux(:,r)*An(:,r)*Ap(:,s).';
    end
end

H = triu(H)+triu(H,1).';
% toc
% end
end