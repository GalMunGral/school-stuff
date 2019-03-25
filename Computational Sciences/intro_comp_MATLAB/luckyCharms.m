function [updated, count] = luckyCharms(sa)
fields = fieldnames(sa);
count = 0;
mask = false(1, length(sa));
for i = 1:length(sa)
    for j = 1:length(fields)
        field = fields{j};
        disp(sa(i).(field));
        if strcmp(sa(i).(field), 'cereal')
            mask(i) = true;
            break;
        end
        if strcmp(sa(i).(field), 'marshmallow')
            count = count + 1;
        end
    end
end
updated = sa(~mask);
end

