rlist = [27,23,22];
errTol=1e-10;
errSwamp=5e-2;
binwidth=0.2;
N=1000;
fmin = zeros(3,N,3);
flast = zeros(3,N,3);
time = zeros(2,N,3);
normx = zeros(3,N,3);
iteration = zeros(3,N,3);


m = 9;
n = 9;
l = 9;
Z = generate_tensor;
f = @(x) objFunc4NormalizedTensorCPD(Z,vec(x),U,V,W,lambdav);

for j=1:3
    r = rlist(j);
    %compute the scaling coefficient of moARC
    U = @(x) reshape(x(1:m*r),[m,r]);
    V = @(x) reshape(x(m*r+1:r*(m+n)),[n,r]);
    W = @(x) reshape(x(r*(m+n)+1:end),[l,r]);
    Zv=reshape(permute(Z,[3,2,1]),[size(Z,1)^3,1]);
    G = @(x) U(x)'*U(x).*(V(x)'*V(x)).*(W(x)'*W(x));
    fv = @(x) sum(khatriraoOptimized(khatriraoOptimized(U(x),V(x)),W(x)).*Zv,1).';
    lambdav = @(x) G(x)\fv(x);
    
    ARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat']);
    SegreARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\SegreARC_' num2str(r) '.mat']);
    moARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\moARC_' num2str(r) '.mat']);
    success = zeros(3);
    swamp = zeros(3,3);
    for i=1:N
        normx(1,i,j) = norm(ARC.x(:,i))^2;
        normx(2,i,j) = norm(SegreARC.x(:,i))^2;
        coeff = lambdav(moARC.x(:,i));
        normx(3,i,j) = norm(coeff)^2;
        errHis=ARC.errorHistory(:,i);
        errHis=errHis(~isnan(errHis));
        flast(1,i,j)=errHis(end);
        fmin(1,i,j)=min(errHis);
        time(1,i,j)=nansum(ARC.Out{i}.time);
    	if min(errHis) <= errTol
            success(1) = success(1) + 1;
        end
        if abs(errHis(end)-0.5) < errSwamp
            swamp(1,1) = swamp(1,1) + 1;
        end
        if abs(errHis(end)-1) < errSwamp
            swamp(2,1) = swamp(2,1) + 1;
        end
        if abs(errHis(end)-1.5) < errSwamp
            swamp(3,1) = swamp(3,1) + 1;
        end
        errHis=SegreARC.errorHistory(:,i);
        errHis=errHis(~isnan(errHis));
        flast(2,i,j)=errHis(end);
        fmin(2,i,j)=min(errHis);
        time(2,i,j)=sum(SegreARC.Out{i}.time);
    	if min(errHis) <= errTol
            success(2) = success(2) + 1;
        end
        if abs(errHis(end)-0.5) < errSwamp
            swamp(1,2) = swamp(1,2) + 1;
        end
        if abs(errHis(end)-1) < errSwamp
            swamp(2,2) = swamp(2,2) + 1;
        end
        if abs(errHis(end)-1.5) < errSwamp
            swamp(3,2) = swamp(3,2) + 1;
        end
        errHis=moARC.errorHistory(:,i);
        errHis(errHis==0) = [];
        flast(3,i,j)=errHis(end);
        fmin(3,i,j)=min(errHis);
    	if min(errHis) <= errTol
            success(3) = success(3) + 1;
        end
        if abs(errHis(end)-0.5) < errSwamp
            swamp(1,3) = swamp(1,3) + 1;
        end
        if abs(errHis(end)-1) < errSwamp
            swamp(2,3) = swamp(2,3) + 1;
        end
        if abs(errHis(end)-1.5) < errSwamp
            swamp(3,3) = swamp(3,3) + 1;
        end
    end
    tottime = squeeze(sum(time,2)/N);
    fprintf("Average time per trial for rank %d:\nARC: %g secs\nSegreARC: %g secs\n",r,tottime(1,j),tottime(2,j))
    fprintf("Rank %d with less than %g in objective function value out of %d trials:\nARC: %d successful trials || %d swamp@0.5 || %d swamp@1 || %d swamp@1.5\nSegreARC: %d successful trials || %d swamp@0.5 || %d swamp@1 || %d swamp@1.5\nmoARC: %d successful trials || %d swamp@0.5 || %d swamp@1 || %d swamp@1.5\n\n",...
        r,errTol,N,success(1),swamp(1,1),swamp(2,1),swamp(3,1),success(2),swamp(1,2),swamp(2,2),swamp(3,2),success(3),swamp(1,3),swamp(2,3),swamp(3,3));
    %histogram
    d1 = log10(flast(1,:,j));                                      
    d2 = log10(flast(2,:,j));    
    d3 = log10(flast(3,:,j));   
    fig1 = figure;
    edges = [-17:0.25:1];
    histogram(d1,edges,'facealpha',0.5,'edgecolor','none');
%     histogram(d1,'BinLimits',[-12 2],'Binwidth',binwidth,'facealpha',0.5,'edgecolor','none');
    hold on
    histogram(d2,edges,'facealpha',0.5,'edgecolor','none');
    histogram(d3,edges,'facealpha',0.5,'edgecolor','none');
%     histogram(d2,'BinLimits',[-12 2],'Binwidth',binwidth,'facealpha',0.5,'edgecolor','none');
%     histogram(d3,'BinLimits',[-4 2],'Binwidth',binwidth,'facealpha',0.5,'edgecolor','none');
%     title(['Rank ' num2str(r) ' Minimum Objective Function Value Histogram'])
    xlabel('log(f(x))')
    ylabel('trial counts')
    legend('ARC','SegreARC','ObliqueARC','location','northeast')
    legend boxoff
    hold off
    export_fig rank27_fmin_histogram -png -transparent
    saveas(fig1,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_fmin_histogram.fig'])
    saveas(fig1,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_fmin_histogram.png'])
    print(fig1, '-dpdf', ['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_fmin_histogram.pdf']);
    %scatter plot
    fig2=figure;
    subplot(3,3,3*(j-1)+1)
    scatter(normx(1,:,j),log10(flast(1,:,j)));
    title(['Rank ' num2str(r) ' ARC'])
    xlabel('norm(x)^2')
    ylabel('log(fval(end))')
    xlim([80 550])
    ylim([-17 1])
%     saveas(fig2,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_ARC_scatterplot.fig'])
%     saveas(fig2,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_ARC_scatterplot.png'])

%     fig3=figure;
    subplot(3,3,3*(j-1)+2)
    scatter(normx(2,:,j),log10(flast(2,:,j)));
    title(['Rank ' num2str(r) ' SegreARC'])
    xlabel('norm(x)^2')
    ylabel('log(fval(end))')
    xlim([80 550])
    ylim([-17 1])
%     saveas(fig3,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_SegreARC_scatterplot.fig'])
%     saveas(fig3,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_SegreARC_scatterplot.png'])

%     fig4=figure;
    subplot(3,3,3*(j-1)+3)
    scatter(log10(normx(3,:,j)),log10(flast(3,:,j)));
    title(['Rank ' num2str(r) ' ObliqueARC'])
    xlabel('log(norm(x)^2)')
    ylabel('log(fval(end))')
    ylim([-17 1])
%     saveas(fig4,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_moARC_scatterplot.fig'])
%     saveas(fig4,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_moARC_scatterplot.png'])
end


    j=1;
    ARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat']);
    SegreARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\SegreARC_' num2str(r) '.mat']);
    moARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\moARC_' num2str(r) '.mat']);
    success = zeros(3);
    swamp = zeros(3,3);
    for i=1:N
        normx(1,i,j) = norm(ARC.x(:,i));
        normx(2,i,j) = norm(SegreARC.x(:,i));
        coeff = lambdav(moARC.x(:,i));
        normx(3,i,j) = norm(coeff);
        errHis=ARC.errorHistory(:,i);
        errHis=errHis(~isnan(errHis));
        flast(1,i,j)=errHis(end);
        fmin(1,i,j)=min(errHis);
        iteration(1,i,j)= size(errHis,1);
    	if min(errHis) <= errTol
            success(1) = success(1) + 1;          
        end
        if abs(errHis(end)-0.5) < errSwamp
            swamp(1,1) = swamp(1,1) + 1;
        end
        if abs(errHis(end)-1) < errSwamp
            swamp(2,1) = swamp(2,1) + 1;
        end
        if abs(errHis(end)-1.5) < errSwamp
            swamp(3,1) = swamp(3,1) + 1;
        end
        errHis=SegreARC.errorHistory(:,i);
%         errHis=errHis(~isnan(errHis));
        errHis(errHis==0) = [];
        flast(2,i,j)=errHis(end);
        fmin(2,i,j)=min(errHis);
        iteration(2,i,j)=SegreARC.Out{i}.iterations-1;
    	if min(errHis) <= errTol
            success(2) = success(2) + 1;
        end
        if abs(errHis(end)-0.5) < errSwamp
            swamp(1,2) = swamp(1,2) + 1;
        end
        if abs(errHis(end)-1) < errSwamp
            swamp(2,2) = swamp(2,2) + 1;
        end
        if abs(errHis(end)-1.5) < errSwamp
            swamp(3,2) = swamp(3,2) + 1;
        end
        errHis=moARC.errorHistory(:,i);
        errHis(errHis==0) = [];
        flast(3,i,j)=errHis(end);
        fmin(3,i,j)=min(errHis);
        iteration(3,i,j)=size(errHis,1);
    	if min(errHis) <= errTol
            success(3) = success(3) + 1;
        end
        if abs(errHis(end)-0.5) < errSwamp
            swamp(1,3) = swamp(1,3) + 1;
        end
        if abs(errHis(end)-1) < errSwamp
            swamp(2,3) = swamp(2,3) + 1;
        end
        if abs(errHis(end)-1.5) < errSwamp
            swamp(3,3) = swamp(3,3) + 1;
        end
    end    
    fig2=figure;
    subplot(1,3,1)
    scatter(normx(1,:,j),log10(flast(1,:,j)),[],iteration(1,:,j),'filled');
    xlabel('norm(x)')
    ylabel('objective function value (1og10)')
    xlim([0 30])
    ylim([-17 1])
    caxis([0 500])

%     saveas(fig2,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_ARC_scatterplot.fig'])
%     saveas(fig2,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_ARC_scatterplot.png'])

%     fig3=figure;
    subplot(1,3,2)
    scatter(normx(2,:,j),log10(flast(2,:,j)),[],iteration(2,:,j),'filled');
    xlabel('norm(x)')
    xlim([0 30])
    ylim([-17 1])
    caxis([0 500])

%     saveas(fig3,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_SegreARC_scatterplot.fig'])
%     saveas(fig3,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_SegreARC_scatterplot.png'])

%     fig4=figure;
    subplot(1,3,3)
    scatter(log10(normx(3,:,j)),log10(flast(3,:,j)),[],iteration(3,:,j),'filled');
    xlabel('log(norm(x))')
    ylim([-17 1])
    colorbar
    colormap jet
    caxis([0 500])
    export_fig rank27_xnorm_scatter -pdf -transparent
    
    fig3=figure;
    subplot(1,3,1)
    scatter(iteration(1,:,j),log10(flast(1,:,j)),[],normx(1,:,j),'filled');
    ylabel('objective function value (1og10)')
    xlim([0 501])
    ylim([-17 1])
    caxis([5 50])

%     saveas(fig2,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_ARC_scatterplot.fig'])
%     saveas(fig2,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_ARC_scatterplot.png'])

%     fig3=figure;
    subplot(1,3,2)
    scatter(iteration(2,:,j),log10(flast(2,:,j)),[],normx(2,:,j),'filled');
    xlabel('iterations')
    xlim([0 501])
    ylim([-17 1])
    caxis([5 50])

%     saveas(fig3,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_SegreARC_scatterplot.fig'])
%     saveas(fig3,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\Rank' num2str(r) '_SegreARC_scatterplot.png'])

%     fig4=figure;
    subplot(1,3,3)
    scatter(iteration(3,:,j),log10(flast(3,:,j)),[],normx(3,:,j),'filled');
    xlim([0 501])
    ylim([-17 1])
    colorbar
    colormap jet
    caxis([5 50])
    export_fig rank27_iter_scatter -pdf -transparent