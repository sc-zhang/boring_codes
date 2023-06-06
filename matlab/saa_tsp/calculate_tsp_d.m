function  result =  calculate_tsp_d(path,d)
% Input:
  % path: a sequence of 1 to n
  % d: distance matrix
% Return:
  % result: the total distance of path
    n = length(path);
    result = 0;
    for i = 1:n-1  
        result = d(path(i),path(i+1)) + result;
    end   
    result = d(path(1),path(n)) + result;
end
