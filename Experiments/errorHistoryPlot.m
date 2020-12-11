rlist = [27,23,22];
maxIts = 501;
for j=1:3
    r = rlist(j);
    
    ARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\ARC_' num2str(r) '.mat']);
    SegreARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\SegreARC_' num2str(r) '.mat']);
    moARC = load(['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\data\moARC_' num2str(r) '.mat']);
    srep=zeros(maxIts,3);
    frep=srep;

    errHis=ARC.errorHistory;
    A=errHis;
    B = ~isnan(A);
    Indices = arrayfun(@(x) find(B(:, x), 1, 'last'), 1:size(A, 2));
    Values = arrayfun(@(x,y) A(x,y), Indices, 1:size(A, 2));
    if r==22
        success=errHis(:,Values<0.5);
        fail=errHis(:,Values>=0.5);  
    else
        success=errHis(:,Values<=1e-10);
        fail=errHis(:,Values>1e-10);
    end
    srep(:,1) = chooseRepTrials(success);
    frep(:,1) = chooseRepTrials(fail);

    errHis=SegreARC.errorHistory(1:501,:);
    A=errHis;
    B = ~isnan(A);
    Indices = arrayfun(@(x) find(B(:, x), 1, 'last'), 1:size(A, 2));
    Values = arrayfun(@(x,y) A(x,y), Indices, 1:size(A, 2));
    if r==22
        success=errHis(:,Values<0.5);
        fail=errHis(:,Values>=0.5);  
    else
        success=errHis(:,Values<=1e-10);
        fail=errHis(:,Values>1e-10);
    end
    srep(:,2) = chooseRepTrials(success);
    frep(:,2) = chooseRepTrials(fail);

    errHis=moARC.errorHistory;
    errHis(errHis==0)=nan;
    A=errHis;
    B = ~isnan(A);
    Indices = arrayfun(@(x) find(B(:, x), 1, 'last'), 1:size(A, 2));
    Values = arrayfun(@(x,y) A(x,y), Indices, 1:size(A, 2));
    if r==22
        success=errHis(:,Values<0.5);
        fail=errHis(:,Values>=0.5);  
    else
        success=errHis(:,Values<=1e-10);
        fail=errHis(:,Values>1e-10);
    end
    srep(:,3) = chooseRepTrials(success);
    frep(:,3) = chooseRepTrials(fail);

    fig=figure;
    colors = get(gca,'colororder');
    colors = colors(1:3,:);
    semilogy(srep,'LineWidth',2,'LineStyle','-');
    hold on
    s2=semilogy(frep,'LineWidth',2,'LineStyle','--');
    hold off
    set(s2,{'color'},mat2cell(colors,[1 1 1],length(colors)));
    legend({'ARC Hit','SegreARC Hit','ObliqueARC Hit','ARC Miss','SegreARC Miss','ObliqueARC Miss'},'Location','southeast')
    legend('boxoff')
    xlabel('iterations')
    ylabel('objective value')
    saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_objval_plot.fig'])
    saveas(fig,['C:\Users\bryan\Documents\GitHub\MatrixMultiplication\Experiments\figures\rank' num2str(r) '_objval_plot.png'])
    fname = sprintf('rank%i_objval_plot', r);
    export_fig(fname,'-pdf','-transparent')
end