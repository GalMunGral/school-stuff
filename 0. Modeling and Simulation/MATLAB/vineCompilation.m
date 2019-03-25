function comp = vineCompilation(vine1, vine2)
    len1 = length(vine1);
    len2 = length(vine2);
    mid = ceil(len1 ./ 2);
    vine1 = [vine1(mid + 1: end) vine1(1: mid)];
    vine2 = sort(vine2, 'descend');
    if len1 < len2
        len = len2;
        vine1(len1+1:len2) = '!';
    else
        len = len1;
        vine2(len2+1:len1) = '!';
    end
    comp = blanks(len);
    for i=1:len
        comp(2*i-1: 2*i) = [vine1(i) vine2(i)];
    end
end

