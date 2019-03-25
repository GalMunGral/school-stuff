function out = stPaddysFeast(sa, start)
curPos = start;
curStruct = sa(curPos(1), curPos(2));
count = 0;
while true
    if strcmp(curStruct.food, 'potato')
        count = count + 1;
    end
    if strcmp(curStruct.food, 'corned beef')
        out = sprintf(['I found %d potatoes before ' ...
            'I reached the corned beef at position (%d,%d).'], count, curPos(1), curPos(2));
        return
    end
    curPos = curStruct.next;
    curStruct = sa(curPos(1), curPos(2));
end
end
