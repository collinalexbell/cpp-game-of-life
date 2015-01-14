#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;


vector<vector<char> > init_board(int h, int w){
//Inits board with random seed based off percentage

  //Percentage of board filled with life
	int i, j, percentage;
	bool cell_is_alive;

	percentage = 20;
	
	vector< vector<char> > rv(h, vector<char>(w, '*'));
	for(i = 0; i < rv.size(); i++){
		for(j = 0; j < rv[i].size(); j++){
			cell_is_alive = (rand()%100 < percentage);
			if(cell_is_alive) rv[i][j] = '@';
		}
	}
	return rv;
}

void print_board(vector<vector<char> > board){
	int i, j;
	for (i = 0; i < board[0].size(); i++){
		for (j = 0; j < board.size(); j++){
			cout << board[j][i];
		}
		cout << endl;
	}
}

int main(){
	srand(time(NULL));
	vector<vector<char> > game_board = init_board(40, 10);
	print_board(game_board);
}
