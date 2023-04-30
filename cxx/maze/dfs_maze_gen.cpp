#include <iostream>
#include <vector>

#define WALL 0
#define ROUTE 1

std::vector<std::vector<int> > directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void disp_maze(std::vector<std::vector<int> > maze){
    for(int i=0; i<maze.size(); i++){
        for(int j=0; j<maze[i].size(); j++){
            if(maze[i][j]==WALL){
                std::cout<<"1";
            }else{
                std::cout<<"0";
            }
        }
        std::cout<<"\n";
    }
}

void init_maze(std::vector<std::vector<int> >& maze, int row, int col){
    for(int i=0; i<row; ++i){
        for(int j=0; j<col; ++j){
            maze[i][0] = ROUTE;
            maze[i][col-1] = ROUTE;
            maze[0][j] = ROUTE;
            maze[row-1][j] = ROUTE;
        }
    }
}

void create_maze(std::vector<std::vector<int> >& maze, int x, int y){
    maze[x][y] = ROUTE;
    
    for(int i=0; i<4; ++i){
        int r = rand()%4;
        if(r!=0){
            swap(directions[0], directions[r]);
        }
    }

    bool is_sel = false;

    int nx, ny;
    for(int i=0; i<4; ++i){
        nx = x+directions[i][0];
        ny = y+directions[i][1];
        is_sel = false;
        if(maze[nx][ny] == ROUTE){
            continue;
        }
        int cnt = 0;
        for(int j=0; j<4; ++j){
            int cx = nx+directions[j][0];
            int cy = ny+directions[j][1];
            if(maze[cx][cy] == ROUTE){
                ++cnt;
            }
        }
        if(cnt>1){
            continue;
        }
        maze[nx][ny] = ROUTE;
        create_maze(maze, nx, ny);
    }
}

int main(int argc, char** argv)
{
    srand(time(0));
    int row, col;
    if(argc==3){
        row = atoi(argv[1]);
        col = atoi(argv[2]);
    }
    std::vector<std::vector<int> > maze(row, std::vector<int>(col, WALL));
    init_maze(maze, row, col);

    create_maze(maze, 2, 2);

    maze[2][1] = ROUTE;
    for(int i=row-3; i>=0; --i){
        if(maze[i][col-3] == ROUTE){
            maze[i][col-2] = ROUTE;
            break;
        }
    }
    disp_maze(maze);
    return 0;
}
