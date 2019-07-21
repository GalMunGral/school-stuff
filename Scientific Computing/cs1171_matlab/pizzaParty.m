function [slices_per_person, left_over] = pizzaParty(num_person, num_pizza)
total_slices = num_pizza .* 8;
slices_per_person = floor(total_slices ./ num_person);
left_over = mod(total_slices, num_person);
end

