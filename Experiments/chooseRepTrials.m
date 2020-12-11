function rep = chooseRepTrials(trials)
if size(trials,2)>0
        itercount = sum(~isnan(trials),1)-1;
        sub = trials(:,findMedianIdx(itercount));
        if size(sub,2) > 1
            A=sub;
            B = ~isnan(A);
            Indices = arrayfun(@(x) find(B(:, x), 1, 'last'), 1:size(A, 2));
            Values = arrayfun(@(x,y) A(x,y), Indices, 1:size(A, 2));
            rep = sub(:,findMedianIdx(Values));
            if size(rep,2) > 1
                rep = rep(:,randi(size(rep,2)));
            end
        else
            rep = sub;
        end
else
        rep = nan;
end
end