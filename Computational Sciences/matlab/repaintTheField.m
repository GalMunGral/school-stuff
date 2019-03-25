function newField = repaintTheField(field,logo)
newField = zeros(size(field));
mask1 = field == '=';
mask2 = field == '|';
mask3 = field == ' ';
m = ~mask1 & ~mask2 & ~mask3;
disp(m);
newField(m) = logo(m);
newField(~m) = field(~m);
newField = char(newField);
end

