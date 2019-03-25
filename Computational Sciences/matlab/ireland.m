function st = ireland(vec)
for i = 1:length(vec)/2
    st.(vec{2*i-1}) = vec{2*i};
end
end

