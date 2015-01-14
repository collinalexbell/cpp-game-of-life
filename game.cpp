#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

typedef vector<vector<char> > board_vector;

board_vector init_board(int h, int w){
//Inits board with random seed based off percentage

  //Percentage of board filled with life
	int i, j, percentage;
	bool cell_is_alive;

	percentage = 15;
	
	board_vector rv;
  rv	=  board_vector(h, vector<char>(w, ' '));
	for(i = 1; i < rv.size()-1; i++){
		for(j = 1; j < rv[i].size()-1; j++){
			cell_is_alive = (rand()%100 < percentage);
			if(cell_is_alive) rv[i][j] = '@';
		}
	}

	// Set boundries
	for (i = 0; i<rv.size(); i++){
		rv[i][0] = rv[i][rv[0].size()-2];
		rv[i][rv[0].size()-1] = rv[i][1];
	}

	for (j = 0; j<rv[0].size(); j++){
		rv[0][j]=rv[rv.size()-2][j];
		rv[rv.size()-1][j]=rv[1][j];
	}
	return rv;
}

void print_board(board_vector board){
	int i, j;
	for (i = 1; i < board[0].size()-1; i++){
		for (j = 1; j < board.size()-1; j++){
			cout << board[j][i];
		}
		cout << endl;
	}
}

void tick(board_vector &board, board_vector &new_board){
	int total_alive, i ,j;
	cout << board.size();
	
	//Iterate through center cells
	for( i = 1; i < board.size()-1; i++ ){
		for( j = 1; j < board[0].size()-1; j++ ){
			total_alive = 0;

			//Left
			if (board[i-1][j] == '@') total_alive += 1;

			//Right
			if (board[i+1][j] == '@') total_alive += 1;

			//Up
			if (board[i][j-1] == '@') total_alive += 1;

			//Down
			if (board[i][j+1] == '@') total_alive += 1;

			//Left-Up
			if (board[i-1][j-1] == '@') total_alive += 1;

			//Right-Up
			if (board[i+1][j-1] == '@') total_alive += 1;

			//Left-Down
			if (board[i-1][j+1] == '@') total_alive += 1;

			//Right-Down
			if (board[i+1][j+1] == '@') total_alive += 1;

			//Update cell
			if(board[i][j] == '@' && total_alive == 2){
				new_board[i][j] = '@';
			}
			else if(total_alive == 3){
				new_board[i][j] = '@';
			}
			else{
				new_board[i][j] = ' ';
			}
		}
	}
	
	// Set buffer
	for (i = 0; i<board.size(); i++){
		new_board[i][0] = board[i][board[0].size()-2];
		new_board[i][board[0].size()-1] = board[i][1];
	}

	for (j = 0; j<board[0].size(); j++){
		new_board[0][j]=board[board.size()-2][j];
		new_board[board.size()-1][j]=board[1][j];
	}
}

int main(){
	srand(time(NULL));
	board_vector *current = new board_vector(init_board(75, 75));
	board_vector *next = new board_vector(*current); 
	cout << current->size();
	while(true){
		system("clear");
		print_board(*current);
		tick(*current, *next);
		swap(current,next);
		usleep(70000);

	}
}
