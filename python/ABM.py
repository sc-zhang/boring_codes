import matplotlib.pyplot as plt
import numpy as np
import random
import argparse
import time


def calc_diff(mat, x, y):
    direct_list = [[-1,0],[1,0],[0,-1],[0,1],[-1,-1],[-1,1],[1,-1],[1,1]]
    cur_type = mat[x][y]
    if cur_type is np.nan:
        return 0
    diff_cnt = 0
    total_cnt = 0
    for off_x, off_y in direct_list:
        nx = x+off_x
        ny = y+off_y
        if nx>=0 and nx<area_edge and ny>=0 and ny<area_edge:
            if not mat[nx][ny] is np.nan:
                total_cnt += 1
                if mat[nx][ny]!=cur_type:
                    diff_cnt += 1
    if total_cnt == 0:
        return 0
    else:
        return diff_cnt*1.0/total_cnt


def unsat_stat(mat, satisf):
    total_cnt = 0
    unsat_cnt = 0
    for x in range(0, area_edge):
        for y in range(0, area_edge):
            if mat[x][y] != 0:
                total_cnt += 1
                diff = calc_diff(mat, x, y)
                if diff > satisf:
                    unsat_cnt += 1
    return unsat_cnt, total_cnt


def ABM(mat, blank_list, area_edge, satisf, iter_cnt):
    if iter_cnt > iter_max:
        return -1
    
    for x in range(0, area_edge):
        for y in range(0, area_edge):
            diff = calc_diff(mat, x, y)
            if (not mat[x][y] is np.nan) and diff > satisf:
                cur_type = mat[x][y]
                cur_pos = x*area_edge+y
                # move to blank site
                idx = random.randint(0, len(blank_list)-1)
                new_pos = blank_list[idx]
                nx = int(new_pos/area_edge)
                ny = new_pos%area_edge
                mat[nx][ny] = cur_type
                mat[x][y] = np.nan
                del blank_list[idx]
                blank_list.append(cur_pos)
    
    unsat = unsat_stat(mat, satisf)
    if unsat[0] == 0:
        return 1
    else:
        return unsat[0]*1.0/unsat[1]


def init_area(area_edge, ele_type, dens):
    blank_list = []
    mat = [[np.nan for j in range(0, area_edge)] for i in range(0, area_edge)]
    area_size = int(area_edge**2)
    # init area
    ele_cnt = int(area_size*dens)
    while ele_cnt>0:
        ele = random.randint(1, ele_type)
        pos = random.randint(0, area_size-1)
        x = int(pos/area_edge)
        y = int(pos%area_edge)
        while not mat[x][y] is np.nan:
            pos = random.randint(0, area_size-1)
            x = int(pos/area_edge)
            y = int(pos%area_edge)
        mat[x][y] = ele
        ele_cnt -= 1

    # init blank list
    for i in range(0, area_edge):
        for j in range(0, area_edge):
            if mat[i][j] is np.nan:
                blank_list.append(i*area_edge+j)
    return mat, blank_list


def visualization(mat, blank_list, area_edge, satisf, iter_max):
    plt.figure(figsize=(area_edge, area_edge))
    ax = plt.gca()
    plt.ion()
    iter_cnt = 0
    ax.imshow(mat, cmap="rainbow")
    time.sleep(1)
    plt.title("Origin")

    res = ABM(mat, blank_list, area_edge, satisf, iter_cnt)

    while iter_cnt < iter_max and res!=-1 and res!=1:
        if iter_cnt%area_edge==0:
            plt.cla()
            ax.imshow(mat, cmap="rainbow")
            plt.title("Iter: %d, Unsat: %.2f%%"%(iter_cnt+1, res*100))
            plt.pause(1)
        print("Iter: %d, Unsat: %.2f%%"%(iter_cnt, res*100))
        iter_cnt += 1
        res = ABM(mat, blank_list, area_edge, satisf, iter_cnt)

    plt.cla()
    ax.imshow(mat, cmap="rainbow")
    if res == 1:
        plt.title("Iter: %d, Unsat: 0.00%%"%iter_cnt)
    else:
        plt.title("Iter: %d, Unsat: NaN"%iter_cnt)
    plt.ioff()
    plt.show()


def get_opts():
    group = argparse.ArgumentParser()
    group.add_argument('-s', '--satisfaction', help='ratio of satifaction, should >0 and <1, default=0.3', type=float, default=0.3)
    group.add_argument('-d', '--density', help='density of element, should >0 and <1, default=0.5', type=float, default=0.5)
    group.add_argument('-e', '--element', help='types of elements, default=3', type=int, default=3)
    group.add_argument('-a', '--area', help='area**2=area size, default=10', type=int, default=10)
    group.add_argument('-i', '--iteration', help='iteration cycles, default=1e6', type=float, default=1e6)
    return group.parse_args()


if __name__ == "__main__":
    opts = get_opts()
    satisf = opts.satisfaction
    dens = opts.density
    ele_type = opts.element
    area_edge = opts.area
    iter_max = opts.iteration
    if satisf <= 0 or satisf >= 1:
        print("Invalid satisfaction value, aborting")
        exit(-1)
    if dens <= 0 or dens >= 1:
        print("Invalid density value, aborting")
        exit(-1)
    if ele_type < 0:
        print("Invalid element value, aborting")
    if area_edge < 0:
        print("Invalid area value, aborting")
    if iter_max < 0:
        print("Invalid iteration value, aborting")
    
    print("Init area")
    mat, blank_list = init_area(area_edge, ele_type, dens)
    
    print("Starting iteration")
    visualization(mat, blank_list, area_edge, satisf, iter_max)
    
    print("Finished")
    