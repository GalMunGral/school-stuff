function updated = plantsVsZombies(filename, column)
[~,~,raw] = xlsread(filename);
header = raw(1,:);
body = raw(2:end,:);

header = [header {'Usefulness'}];
defense = cell2mat(body(:,strcmpi(header, 'Defense')));
attack = cell2mat(body(:,strcmpi(header, 'Attack')));
body(:,end+1) = num2cell(defense + attack);

idx = find(strcmpi(header, column));
sortedBody = sortrows(body, idx, 'descend');
updated = [header; sortedBody(1:3,:)];

end

