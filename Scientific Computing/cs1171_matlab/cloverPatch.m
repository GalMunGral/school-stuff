function updated = cloverPatch(sa, field)
for i = 1:length(sa)
    luck = 0;
    luck = luck + sa(i).numLeaves * 25;
    if ~strcmp(sa(i).color, 'green')
        luck = luck - 50;
    end
    luck = luck + sa(i).isLeprechaun * 317;
    luck = luck + sa(i).(field);
    sa(i).luck = luck;
end
luckVec = [sa.luck];
[~, I] = sort(luckVec, 'descend');
updated = sa(I);
updated = rmfield(updated, field);
end

