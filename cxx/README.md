## C/C++ codes
### Sudoku Solver
A simple program for solving sudoku problem
```bash
g++ -O3 -o SudokuSolver SudokuSolver.cpp
# input 81 digit or -, - means missing
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

### Sort
- Heapsort
A simple implement of heapsort
```bash
cd sort
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
# input two sequences
```

### Maze
- DFS Maze Generator
A simple maze generator based on dfs
```bash
cd maze
g++ -O3 -o dfs_maze_gen dfs_maze_gen.cpp --std=c++11
# input two numbers, means row count and column count
```

### Tower of Hanoi
Tower of Hanoi Sovler
```bash
g++ -O3 -o hanoi hanoi.cpp
# input number, means plate counts
```

### A/B Guess Number
A/B Number Guess Game
Guess a non-repeat 4-digit number, number with correct number and position will mark as A, number with correct number but wrong position as B.
```bash
g++ -O3 -o ABGuessNumber ABGuessNumber.cpp
# input 4-digit number, you can guess 10 times.
```
