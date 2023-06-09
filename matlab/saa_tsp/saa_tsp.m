function saa_tsp(city_count)
    %% Solve tsp problem with saa
    rng('shuffle')
    
    %% generate new cities
    coord = gen_new_coord(city_count);
    n = size(coord,1);

    d = zeros(n);
    for i = 2:n  
        for j = 1:i  
            coord_i = coord(i,:); x_i = coord_i(1); y_i = coord_i(2);
            coord_j = coord(j,:); x_j = coord_j(1); y_j = coord_j(2);
            d(i,j) = sqrt((x_i-x_j)^2 + (y_i-y_j)^2);
        end
    end
    d = d+d';

    tic
    T0 = 1000; % the origin temperature
    T = T0; % temperature of each iteration
    Tfinal = 0.0001; % final temperature
    test_count = 500; % for each iteration, test 500 times
    alpha = 0.95; % coefficient of temperatue drop

    path0 = randperm(n);
    result0 = calculate_tsp_d(path0,d);

    min_result = result0;
    iter_count = 0;
    while T > Tfinal
        T = T*alpha;
        iter_count = iter_count + 1;
    end
    T = T0;
    RESULT = zeros(iter_count, 1);
    iter_count = 1;
    while T > Tfinal
        % for each temperature test iter times
        for i = 1 : test_count
            path1 = gen_new_path(path0);
            result1 = calculate_tsp_d(path1,d);
            if result1 < result0    
                path0 = path1;
                result0 = result1; 
            else
                p = exp(-(result1 - result0)/T);
                if rand(1) < p
                    path0 = path1;
                    result0 = result1; 
                end
            end
            if result0 < min_result
                min_result = result0;
                best_path = path0;
            end
        end
        RESULT(iter_count) = min_result;
        iter_count = iter_count + 1;
        T = alpha*T;
    end

    disp('Best path: '); disp(mat2str(best_path))
    disp('Best distance: '); disp(min_result)
    
    toc
    
    if city_count <= 1000
        fig = figure;
        set(fig,'units','normalized','position',[0.1 0.1 0.8 0.8]);
        plot(coord(:,1), coord(:,2), 'o');
        hold on
        best_path = [best_path,best_path(1)];
        n = n+1;
        for i = 1:n-1 
            j = i+1;
            coord_i = coord(best_path(i),:); x_i = coord_i(1); y_i = coord_i(2); 
            coord_j = coord(best_path(j),:); x_j = coord_j(1); y_j = coord_j(2);
            plot([x_i,x_j],[y_i,y_j],'g-')
            pause(0.001)
            hold on
        end
    end

    figure
    plot(1:iter_count-1,RESULT,'b-');
    xlabel('Iter count');
    ylabel('Minium distance');
end
