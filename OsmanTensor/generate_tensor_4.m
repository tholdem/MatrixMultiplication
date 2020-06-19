function X = generate_tensor_4
% This script reproduces the tensor indices on page 30 of Tammy's tensor
% tutorial slides. 

idx = [(1:4).' repmat([1:2].',2,1) repelem([1:2].',2,1)];
X = zeros(4,4,4);
u = zeros(8,1);
v = zeros(8,1);
w = zeros(8,1);
cnt = 1;

%r = 1;

for i = 1:4
    for j = 1:4
        for k = 1:4
            if idx(i, 2) == idx(k, 2) && idx(j, 3) == idx(k, 3) && idx(i, 3) == idx(j, 2)
                disp(['(', num2str(i), ',', num2str(j), ',', num2str(k), ')']);
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
