function out = solitaire(cards)
cards = sort(cards);
found = false;
if cards(1) == 1
    out = 'Move the Ace.';
else
    for i = 1:length(cards)-1
        if cards(i+1)-cards(i) == 1
            out = sprintf('Put the %d on the %d.', cards(i), cards(i+1));
            found = true;
            break
        end
    end
    if ~found
        out = 'Draw from the deck.';
    end
end
end
