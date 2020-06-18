function errHist = simpleHessianCheck( g, H, x0, varargin )

prs = inputParser;
addParameter(prs,'nReps', 5 );
addParameter(prs,'d', [] );
addParameter(prs,'nSteps', [] );
addParameter(prs,'hScaling', 1 );
addParameter(prs,'hDecrease', 10 );
addParameter(prs,'x0Scaling', 1 );
addParameter(prs,'plotting', false );

parse(prs,varargin{:});

nReps       = prs.Results.nReps;
d           = prs.Results.d;
nSteps      = prs.Results.nSteps;
hScaling    = prs.Results.hScaling;
hDecrease   = prs.Results.hDecrease;
x0Scaling   = prs.Results.x0Scaling;
plotting   = prs.Results.plotting;

if plotting
    % change the defaults
    % Override hDecrease
    if isempty( nSteps), nSteps = 50; end
    hGrid   = logspace( log10(hScaling), -14, nSteps );
    hDecrease   = hGrid(1)/hGrid(2);
    nReps   = 1;
else
    if isempty( nSteps), nSteps = 5; end
end

if ~plotting
    fprintf('============================================================\n');
    fprintf('h\t\tForward d\tCentral d\t Order decrease\n');
end
for n = 1:nReps
    if n==1
        x   = x0;
    else
        x   = x0 + x0Scaling*randn(size(x0));
    end
    if isempty(d) || n > 1
        d   = x0Scaling*randn(size(x0));
    end
    
    h   = hScaling;
    errHist = zeros(nSteps,3);
    if ~plotting, fprintf('------------------------------------------------------------\n'); end
    for k = 1:nSteps
        g0  = g(x);
        gA  = g(x+h*d);
        gB  = g(x-h*d);
%        Hx  = H(d,x);%x is x0, d is the step direction
        Hx  = H(x,d);
        errHist(k,1)    = norm( (gA-g0)/h - Hx );     % forward diff
        errHist(k,2)    = norm( (gA-gB)/(2*h) - Hx ); % central diff
        errHist(k,3)    = h;
        
        if nSteps < 20
            fprintf('%.2e\t%.2e\t%.2e', h, errHist(k,1), errHist(k,2) );
            chg     = @(relChange) log10( relChange )/log10(hDecrease);
            if k > 1
                fprintf('\t%.1fx\t%.1fx', chg(errHist(k-1,1)/errHist(k,1) ), ...
                    chg(errHist(k-1,2)/errHist(k,2) ) );
            end
            
            fprintf('\n');
            
        end
        
        h   = h/hDecrease;
    end
    
end
if plotting
    figure;
    hl=loglog( errHist(:,3), errHist(:,1:2), 'linewidth', 2  );
    xlabel('stepsize');
    
    [mn,ind]    = min( errHist(:,1) );
    xx  = [.5*errHist(ind,3),2*errHist(1,3)];
    line( xx, (xx/xx(2)).^1*errHist(1,1) ,'linewidth',2,'linestyle','--','color',[0.9290    0.6940    0.1250]);
    
    [mn,ind]    = min( errHist(:,2) );
    xx  = [.5*errHist(ind,3),2*errHist(1,3)];
    % line( [errHist(ind,3),errHist(1,3)], [mn,errHist(1,2)] );
    line( xx, (xx/xx(2)).^2*errHist(1,2)  ,'linewidth',2,'linestyle','--','color',[0.4940    0.1840    0.5560]);
    
    % axis square
    grid on
%     axis equal
    xlim( [min(errHist(:,3)),max(errHist(:,3)) ] );
    
    legend('Forward diff','Centered diff','1st order','2nd order','location','northwest');
    set(gca,'fontsize',24)
    title('Forward diff should be 1st order; centered diff should be 2nd order');
    % Make figure bigger
    pos = get(gcf,'Position');
    set(gcf,'Position',[pos(1),pos(2),1200,800]);
    movegui([300 100]);
    
end