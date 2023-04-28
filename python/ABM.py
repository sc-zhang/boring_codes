import matplotlib.pyplot as plt
import numpy as np
import random
import sys


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


def unsat_stat(mat, per_sim):
    total_cnt = 0
    unsat_cnt = 0
    for x in range(0, area_edge):
        for y in range(0, area_edge):
            if mat[x][y] != 0:
                total_cnt += 1
                diff = calc_diff(mat, x, y)
                if diff > per_sim:
                    unsat_cnt += 1
    return unsat_cnt, total_cnt


def ABM(mat, blank_list, area_edge, per_sim, iter_cnt):
    if iter_cnt > iter_max:
        return -1
    
    for x in range(0, area_edge):
        for y in range(0, area_edge):
            diff = calc_diff(mat, x, y)
            if (not mat[x][y] is np.nan) and diff > per_sim:
                cur_type = mat[x][y]
                cur_pos = x*area_edge+y
                if len(blank_list) == 0:
                    nx = random.randint(0, area_edge-1)
                    ny = random.randint(0, area_edge-1)
                    while nx==x and ny==y:
                        nx = random.randint(0, area_edge-1)
                        ny = random.randint(0, area_edge-1)
                    tmp = mat[x][y]
                    mat[x][y] = mat[nx][ny]
                    mat[nx][ny] = tmp
                else:
                    idx = random.randint(0, len(blank_list)-1)
                    new_pos = blank_list[idx]
                    nx = int(new_pos/area_edge)
                    ny = new_pos%area_edge
                    mat[nx][ny] = cur_type
                    mat[x][y] = np.nan
                    del blank_list[idx]
                    blank_list.append(cur_pos)
    unsat = unsat_stat(mat, per_sim)
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


def visualization(mat, blank_list, area_edge, per_sim, iter_max):
    plt.figure(figsize=(area_edge, area_edge))
    ax = plt.gca()
    plt.ion()
    iter_cnt = 0
    ax.imshow(mat, cmap="rainbow")
    plt.title("Origin")
    plt.savefig("origin.pdf", bbox_inches='tight')
    print("Origin area saved")
    res = ABM(mat, blank_list, area_edge, per_sim, iter_cnt)
    
    while res!=-1 and res!=1:
        if iter_cnt%1==0:
            plt.cla()
            ax.imshow(mat, cmap="rainbow")
            plt.title("Iter: %d, Unsat: %.2f%%"%(iter_cnt+1, res*100))
            plt.pause(0.1)
        print("Iter: %d, Unsat: %.2f%%"%(iter_cnt, res*100))
        iter_cnt += 1
        res = ABM(mat, blank_list, area_edge, per_sim, iter_cnt)

    plt.cla()
    ax.imshow(mat, cmap="rainbow")
    if res == 1:
        plt.title("Iter: %d, Unsat: 0.00%%"%iter_cnt)
    else:
        plt.title("Iter: %d, Unsat: NaN"%iter_cnt)
    plt.savefig("final.pdf", bbox_inches='tight')
    plt.ioff()
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) < 6:
        print("Usage: python %s <permit_sim> <density> <element_type_count> <area_edge_length> <iteration_max_count>"%sys.argv[0])
        sys.exit(-1)
    per_sim = float(sys.argv[1])
    dens = float(sys.argv[2])
    ele_type = int(sys.argv[3])
    area_edge = int(sys.argv[4])
    iter_max = int(sys.argv[5])

    print("Init area")
    mat, blank_list = init_area(area_edge, ele_type, dens)
    
    print("Starting iteration")
    visualization(mat, blank_list, area_edge, per_sim, iter_max)
    
    print("Finished")
 
