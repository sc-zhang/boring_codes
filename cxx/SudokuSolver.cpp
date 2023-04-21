#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Solution{
public:
	int getPossible(vector<vector<char> >& board, int row, int col){
		// 511 = 0b111111111 means 1~9
		int possibleNums=511;
		int impossibleNum;
		for(int i=0;i<9;i++){
			// remove impossible nums by check numbers in same row
			if(i!=col&&board[row][i]!='.'){
				impossibleNum = board[row][i]-'1';
				impossibleNum = 1<<impossibleNum;
				possibleNums &= (511-impossibleNum);
			}
			// remove impossible nums by check numbers in same column
			if(i!=row&&board[i][col]!='.'){
				impossibleNum = board[i][col]-'1';
				impossibleNum = 1<<impossibleNum;
				possibleNums &= (511-impossibleNum);
			}
			// remove impossible nums by check numbers in same 3*3 grid
			if(i/3!=row%3&&i%3!=col%3&&board[row/3*3+i/3][col/3*3+i%3]!='.'){
				impossibleNum = board[row/3*3+i/3][col/3*3+i%3]-'1';
				impossibleNum = 1<<impossibleNum;
				possibleNums &= (511-impossibleNum);
			}
		}
		return possibleNums;
	}

	// extract possible numbers to vector
	vector<int> getPossibleNums(int possible){
		vector<int> res;
		int i=1;
		while(possible){
			if(possible&1){
				res.push_back(i);
			}
			i++;
			possible>>=1;
		}
		return res;
	}

	bool dfs(vector<vector<char> >& board, int position, int blank){
		int possible;
		int check;
		int row=position/9;
		int col=position%9;
		vector<int> possibleNums;

		// if current position is empty, select one possible number, and dfs
		if(board[row][col] == '.'){
			possible = getPossible(board, row, col);
			if(possible==0){
				return false;
			}else{
				possibleNums = getPossibleNums(possible);
				// use random shuffle, this program can also used for generating sudoku game.
				random_shuffle(possibleNums.begin(), possibleNums.end());
				for(int i=0; i<possibleNums.size();i++){
					board[row][col] = possibleNums[i]+'0';
					blank--;
					// only when no blank left, the problem is solved
					if(blank==0){
						return true;
					}
					if(dfs(board, position+1, blank)){
						return true;
					};
					board[row][col] = '.';
					blank++;
				}
			}
		}
		// else move to next position, and dfs
		else{
			if(dfs(board, position+1, blank)){
				return true;
			};
		}
		return false;
	}

	// count blank, then start dfs from 1st position
	bool solveSudoku(vector<vector<char> >& board){
		int blank=0;
		for(int row=0;row<9;row++){
			for(int col=0;col<9;col++){
				if(board[row][col]=='.'){
					blank++;
				}
			}
		}
		return dfs(board, 0, blank);
	}
};


class Board{
public:
	vector<vector<char> > board;
	Board(){
		vector<char> tmp;
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				tmp.push_back('.');
			}
			this->board.push_back(tmp);
			tmp.clear();
		}
	}
	Board(vector<vector<char> > board){
		this->board = board;
	}
	void SetVal(vector<vector<char> > board){
		this->board = board;
	}
	void PrintBoard(){
		for(int i=0; i<board.size(); i++){
			if(i%3==0){
				cout<<"++===+===+===++===+===+===++===+===+===++\n";
			}else{
				cout<<"++---+---+---++---+---+---++---+---+---++\n";
			}
			for(int j=0; j<board[i].size(); j++){
				if(j%3==0){
					cout<<"|| "<<board[i][j]<<" ";
				}else{
					cout<<"| "<<board[i][j]<<" ";
				}
			}
			cout<<"||\n";
		}
		cout<<"++===+===+===++===+===+===++===+===+===++\n";
	}
};

int main(){
	int n = 81;
	vector< vector<char> > board;
	vector<char> tmp;

	srand((unsigned int)time(0));
	cout<<"Input numbers in sudoku game, input \".\" for missing, seperate with space\n";
	while(n>0){
		char i;
		cin>>i;
		tmp.push_back(i);
		n--;
		
		if(n%9==0){
			board.push_back(tmp);
			tmp.clear();
		}
	}
	
	Board newboard(board);
	cout<<"Origin:\n";
	newboard.PrintBoard();
	Solution s;
	
	if(s.solveSudoku(newboard.board)){
		cout<<"\nSolved:\n";
		newboard.PrintBoard();
	}
	else{
		cout<<"\nNo Answer\n";
	}
	return 0;
}
