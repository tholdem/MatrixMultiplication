rank = 22;
errThd = 1e-6;
datadir = 'C:\Users\bryan\Documents\Research\output\rank' + string(rank)+'_error'+string(errThd)';
figuredir = 'C:\Users\bryan\Documents\Research\figures\rank' + string(rank)+'_error'+string(errThd);
mkdir(figuredir);
low = 0;
middle = 0;
high = 0;
saddle = 0;
fail = 0;
for i=1:1000
    filename = string(datadir) + '/rank' + string(rank) + '_error' + string(errThd) + '_' + string(i) + '.mat';
    figurename = string(figuredir) + '/rank' + string(rank) + '_error' + string(errThd) + '_' + string(i) + '.png';
    try
        load(filename);
    catch ME
        disp('Error Message:')
        disp(ME.message)
        continue
    end
    %failed
    if errorHistory == 0
        fail = fail + 1;
        continue
    end
    %remove the zeros at the end, so the last entry comes from data
    errorHistory(errorHistory==0) = [];
    if errorHistory(end)<= 1e-12
        low = low+1;
    elseif errorHistory(end)<= 1e-6
        middle = middle + 1;
    elseif errorHistory(end)<= 1e-2
        high = high + 1;
    else
        saddle = saddle + 1;
    end
    h=figure;
    set(h,'visible','off')
    semilogy(errorHistory);
    xlabel('iterations');
    ylabel('f(x)');
    saveas(h,figurename,'png');
end
fprintf('There are %d lows, %d middles, %d highs, %d saddles, and %d fails.\n',low,middle,high,saddle,fail);