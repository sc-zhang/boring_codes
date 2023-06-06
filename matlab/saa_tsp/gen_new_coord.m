function coord = gen_new_coord(city_count)
  % Input:
    % city_count: the cities for travel
  % Return:
    % coord: a set of [x, y] of cities
    rng('shuffle');
    coord = zeros(city_count, 2);
    for i = 1:city_count*2
       coord(i) = rand()*1e4;
    end
end
