function X = generate_tensor %#codegen
% This script reproduces the tensor indices on page 30 of Tammy's tensor
% tutorial slides. 
idx = [(1:9).' repmat([1,2,3].',3,1) repelem([1,2,3].',3,1)];
X = zeros(9,9,9);
u = zeros(27,1);
v = zeros(27,1);
w = zeros(27,1);
cnt = 1;

%r = 1;

for i = 1:9
    for j = 1:9
        for k = 1:9
            if idx(i, 2) == idx(k, 2) && idx(j, 3) == idx(k, 3) && idx(i, 3) == idx(j, 2)
                %c_1 = C_{1,1} = sum_j A_{1,j} B_{j,1}
                %the row index of element of C to match row index of A, column index of C to match column index of B, and the column index of A matches the row index of B
                %this is column-wise: Jaden Wang June 2020
                %disp(['(', num2str(i), ',', num2str(j), ',', num2str(k), ')']);
                X(i,j,k) = 1;
                u(cnt) = i;
                v(cnt) = j;
                w(cnt) = k;
                %Y{1}(i,r) = 1;
                %Y{2}(j,r) = 1;
                %Y{3}(k,r) = 1;
                %r = r+1;
                cnt = cnt+1;
            end
        end
    end
end
%sanity check
% D = zeros(9,1);
% for k=1:9
%     D(k) =a'*Z(:,:,k)*b;
% end