#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

class Solution{
public:
	int getPossible(vector<vector<char> >& board, int i, int j){
		int a=511;
		int pos;
		for(int k=0;k<9;k++){
			if(k!=j&&board[i][k]!='.'){
				pos = board[i][k]-'1';
				pos = 1<<pos;
				a &= (511-pos);
			}
			if(k!=i&&board[k][j]!='.'){
				pos = board[k][j]-'1';
				pos = 1<<pos;
				a &= (511-pos);
			}
			if(k/3!=i%3&&k%3!=j%3&&board[i/3*3+k/3][j/3*3+k%3]!='.'){
				pos = board[i/3*3+k/3][j/3*3+k%3]-'1';
				pos = 1<<pos;
				a &= (511-pos);
			}
		}
		return a;
	}

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

	bool dfs(vector<vector<char> >& board, int pos, int blank){
		int possible;
		int check;
		int i=pos/9;
		int j=pos%9;
		vector<int> possibleNums;

		if(board[i][j] == '.'){
			possible = getPossible(board, i, j);
			if(possible==0){
				return false;
			}else{
				possibleNums = getPossibleNums(possible);
				for(int k=0; k<possibleNums.size();k++){
					board[i][j] = possibleNums[k]+'0';
					blank--;
					if(blank==0){
						return true;
					}
					if(dfs(board, pos+1, blank)){
						return true;
					};
					board[i][j] = '.';
					blank++;
				}
			}
		}else{
			if(dfs(board, pos+1, blank)){
				return true;
			};
		}
		return false;
	}

	void solveSudoku(vector<vector<char> >& board){
		int blank=0;
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(board[i][j]=='.'){
					blank++;
				}
			}
		}
		dfs(board, 0, blank);
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
		for(vector<vector<char> >::iterator iteri=this->board.begin(); iteri!=this->board.end();iteri++){
			for(vector<char>::iterator iterj=iteri->begin();iterj!=iteri->end();iterj++){
				cout<<*iterj<<' ';
			}
			cout<<endl;
		}
	}
};

int main(){
	int n = 81;
	vector< vector<char> > board;
	vector<char> tmp;

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
	cout<<"=====Before=====\n";
	newboard.PrintBoard();
	Solution s;
	cout<<"=====After=====\n";
	s.solveSudoku(newboard.board);
	newboard.PrintBoard();
	return 0;
}