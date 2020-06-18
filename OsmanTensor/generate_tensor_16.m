% Generates the 16 x 16 x 16 tensor corresponding to 4 x 4 matrix
% multiplication.

N = 4;

idx = [(1:N^2).' repmat([1:N].',N,1) repelem([1:N].',N,1)];
X = zeros(N^2,N^2,N^2);
u = zeros(N^3,1);
v = zeros(N^3,1);
w = zeros(N^3,1);
cnt = 1;

for i = 1:N^2
    for j = 1:N^2
        for k = 1:N^2
            if idx(i, 2) == idx(k, 3) && idx(j, 3) == idx(k, 2) && idx(i, 3) == idx(j, 2)
                disp(['(', num2str(i), ',', num2str(j), ',', num2str(k), ')']);
                X(i,j,k) = 1;
                u(cnt) = i;
                v(cnt) = j;
                w(cnt) = k;
                cnt = cnt+1;
            end
        end
    end
end
