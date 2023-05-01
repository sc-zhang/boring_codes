## C/C++ codes
### Sudoku Solver
A simple program for solving sudoku problem
```bash
g++ -O3 -o SudokuSolver SudokuSolver.cpp
```

### Gaussian Elimination
A simple program for solving linear equation group。
```bash
g++ -O3 -o GaussianElimination GaussianElimination.cpp
# input
# a number n for order
# n*n+1 numbers for matrix
# like:
# 4
# 1 1 1 1 4
# 2 1 1 1 5
# 3 2 1 1 7
# 4 3 2 1 10 
```

### Heapsort
A simple implement of heapsort
```bash
g++ -O3 -o heapsort heapsort.cpp
# input
# a number n
# n numbers for sorting
```

### Sequence Alignment
A simple implement of Needleman-Wunsch and Smith-Waterman algorithm
```bash
g++ -O3 -o global_align global_align.cpp
g++ -O3 -o local_align local_align.cpp
```

### Maze
- DFS Maze Generator
A simple maze generator based on dfs
```bash
cd maze
g++ -O3 -o dfs_maze_gen dfs_maze_gen.cpp --std=c++11
```
