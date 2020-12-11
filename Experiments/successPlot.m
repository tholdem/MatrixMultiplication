rlist = [27,23];
errTol=1e-10;
maxIts= 501;
N=1000;
counts=zeros(maxIts,3);
for j = 1:2
    r = rlist(j);
    ARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat']);
    SegreARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\SegreARC_' num2str(r) '.mat']);
    moARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\moARC_' num2str(r) '.mat']);
    for i = 1:N
        errorHistory = ARC.errorHistory(:,i);
        errorHistoryTemp = errorHistory;
        errorHistoryTemp = errorHistoryTemp(~isnan(errorHistoryTemp));
        last = errorHistoryTemp(end);
        errorHistory(isnan(errorHistory)) = last;
        ARC.errorHistory(:,i) = errorHistory;
        
        errorHistory = SegreARC.errorHistory(:,i);
        errorHistoryTemp = errorHistory;
        errorHistoryTemp = errorHistoryTemp(~isnan(errorHistoryTemp));
        last = errorHistoryTemp(end);
        errorHistory(isnan(errorHistory)) = last;
        SegreARC.errorHistory(:,i) = errorHistory;
        
        errorHistory = moARC.errorHistory(:,i);
        errorHistoryTemp = errorHistory;
        errorHistoryTemp (errorHistoryTemp ==0) = [];
        last = errorHistoryTemp(end);
        errorHistory(errorHistory==0) = last;
        moARC.errorHistory(:,i) = errorHistory;
    end
    for i = 1:maxIts
        counts(i,1) = sum(ARC.errorHistory(i,:) < errTol);
        counts(i,2) = sum(SegreARC.errorHistory(i,:) < errTol);
        counts(i,3) = sum(moARC.errorHistory(i,:) < errTol);
    end
    fig=figure;
    ax = axes;
    x=[1:maxIts];
    plot(x,counts/10,'LineWidth',2)
    ytickformat(ax, 'percentage');

%     title(['Rank ' num2str(r) ' Success Counts vs Iterations'])
    xlabel('iterations')
    ylabel('percentage of trials that found a solution')
    xlim([0 maxIts])
%     ylim([0 N])
    legend({'ARC','SegreARC','ObliqueARC'},'Location','northeast')
    legend('boxoff')
    saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_success_plot.fig'])
    saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_success_plot.png'])
    fname = sprintf('rank%i_success_plot', r);
    export_fig(fname,'-pdf','-transparent')
end

for j = 1:2
    r = rlist(j);
    ARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat']);
    SegreARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\SegreARC_' num2str(r) '.mat']);
    Segre2ARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\Segre2ARC_' num2str(r) '.mat']);
    for i = 1:N
        errorHistory = ARC.errorHistory(:,i);
        errorHistoryTemp = errorHistory;
        errorHistoryTemp = errorHistoryTemp(~isnan(errorHistoryTemp));
        last = errorHistoryTemp(end);
        errorHistory(isnan(errorHistory)) = last;
        ARC.errorHistory(:,i) = errorHistory;
        
        errorHistory = SegreARC.errorHistory(:,i);
        errorHistoryTemp = errorHistory;
        errorHistoryTemp = errorHistoryTemp(~isnan(errorHistoryTemp));
        last = errorHistoryTemp(end);
        errorHistory(isnan(errorHistory)) = last;
        SegreARC.errorHistory(:,i) = errorHistory;
        
        errorHistory = Segre2ARC.errorHistory(:,i);
        errorHistoryTemp = errorHistory;
        errorHistoryTemp = errorHistoryTemp(~isnan(errorHistoryTemp));
        last = errorHistoryTemp(end);
        errorHistory(isnan(errorHistory)) = last;
        Segre2ARC.errorHistory(:,i) = errorHistory;
    end
    for i = 1:maxIts
        counts(i,1) = sum(ARC.errorHistory(i,:) < errTol);
        counts(i,2) = sum(SegreARC.errorHistory(i,:) < errTol);
        counts(i,3) = sum(Segre2ARC.errorHistory(i,:) < errTol);
    end
    fig=figure;
    ax = axes;
    x=[1:maxIts];
    plot(x,counts/10,'LineWidth',2)
    ytickformat(ax, 'percentage');

%     title(['Rank ' num2str(r) ' Success Counts vs Iterations'])
    xlabel('iterations')
    ylabel('percentage of trials that found a solution')
    xlim([0 maxIts])
%     ylim([0 N])
    legend({'ARC','SegreARC','Segre2ARC'},'Location','northeast')
    legend('boxoff')
    saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_success_plot.fig'])
    saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_success_plot.png'])
    fname = sprintf('rank%i_success_plot', r);
    export_fig(fname,'-pdf','-transparent')
end