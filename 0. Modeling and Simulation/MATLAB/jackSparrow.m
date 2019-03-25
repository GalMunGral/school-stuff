function out = jackSparrow(my_hand, jacks_hand, cards)
% My move
while true
    total = sum(my_hand);
    if total < 12
        my_hand = [my_hand cards(1)];
        cards = cards(2:end);
    elseif total >= 17
        break
    else
        if jacks_hand(1) >= 2 && jacks_hand(1) <= 6
            break
        else
            my_hand = [my_hand cards(1)];
            cards = cards(2:end);
        end
    end
end
% Jack's move
while sum(jacks_hand) < 17
    jacks_hand = [jacks_hand cards(1)];
    cards = cards(2:end);
end
my_total = sum(my_hand);
jacks_total =sum(jacks_hand);
if my_total > 21 && jacks_total > 21
    out = 'Oh no! We both hornswoggled.';
elseif my_total > 21
    out = 'Jack Sparrow wins.';
elseif jacks_total > 21
    out = 'Blimey! I win!';
elseif my_total > jacks_total
    out = 'Blimey! I win!';
else
    out = 'Jack Sparrow wins.';
end       
end

