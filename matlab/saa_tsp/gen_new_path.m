function path1 = gen_new_path(path0)
    % path0: origin path
    n = length(path0);
    % random select the path generate algorithm
    p1 = 0.33;  % probability of swap
    p2 = 0.33;  % probability of shift
    r = rand(1);
    if  r< p1
      % generate new path by swapping two points
        c1 = randi(n);
        c2 = randi(n);
        path1 = path0;
        path1(c1) = path0(c2);
        path1(c2) = path0(c1);
    elseif r < p1+p2
      % generate new path by shifting
        c1 = randi(n);
        c2 = randi(n);
        c3 = randi(n);
        sort_c = sort([c1 c2 c3]);
        c1 = sort_c(1);  c2 = sort_c(2);  c3 = sort_c(3);
        tem1 = path0(1:c1-1);
        tem2 = path0(c1:c2);
        tem3 = path0(c2+1:c3);
        tem4 = path0(c3+1:end);
        path1 = [tem1 tem3 tem2 tem4];
    else
      % generate new path by inverting
        c1 = randi(n);
        c2 = randi(n);
        if c1>c2
            tem = c2;
            c2 = c1;
            c1 = tem;
        end
        tem1 = path0(1:c1-1);
        tem2 = path0(c1:c2);
        tem3 = path0(c2+1:end);
        path1 = [tem1 fliplr(tem2) tem3];
    end
end
