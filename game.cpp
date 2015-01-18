#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "gui.h"

using namespace std;

typedef vector<vector<char> > board_vector;

class Life_Board{

	public:
		Life_Board(int h, int w){

			srand(time(NULL));
			//Inits board with random seed based off percentage

			//Percentage of board filled with life
			int i, j, percentage;
			bool cell_is_alive;

			percentage = 15;

			current	=  new board_vector(h, vector<char>(w, ' '));
			next = new board_vector(h, vector<char>(w, ' '));
			for(i = 1; i < current->size()-1; i++){
				for(j = 1; j < (*current)[i].size()-1; j++){
					cell_is_alive = (rand()%100 < percentage);
					if(cell_is_alive) (*current)[i][j] = '@';
				}
			}

			// Set boundries
			for (i = 0; i<current->size(); i++){
				(*current)[i][0] = (*current)[i][(*current)[0].size()-2];
				(*current)[i][(*current)[0].size()-1] = (*current)[i][1];
			}

			for (j = 0; j<(*current)[0].size(); j++){
				(*current)[0][j]=(*current)[current->size()-2][j];
				(*current)[current->size()-1][j]=(*current)[1][j];
			}
		}


		void print(){
			int i, j;
			for (i = 1; i < (*current)[0].size()-1; i++){
				for (j = 1; j < current->size()-1; j++){
					cout << (*current)[j][i];
				}
				cout << endl;
			}
		}

		void gui_print(GUI_Board gui){
			gui.clear();
			int i, j;
			for (i = 1; i < (*current)[0].size()-1; i++){
				for (j = 1; j < current->size()-1; j++){
					if((*current)[j][i] == '@') gui.draw_circle(j-1,i-1);
				}
			}
			gui.update();
		}

		void tick(){
			int total_alive, i ,j;

			//Iterate through center cells
			for( i = 1; i < current->size()-1; i++ ){
				for( j = 1; j < (*current)[0].size()-1; j++ ){
					total_alive = 0;

					//Left
					if ((*current)[i-1][j] == '@') total_alive += 1;

					//Right
					if ((*current)[i+1][j] == '@') total_alive += 1;

					//Up
					if ((*current)[i][j-1] == '@') total_alive += 1;

					//Down
					if ((*current)[i][j+1] == '@') total_alive += 1;

					//Left-Up
					if ((*current)[i-1][j-1] == '@') total_alive += 1;

					//Right-Up
					if ((*current)[i+1][j-1] == '@') total_alive += 1;

					//Left-Down
					if ((*current)[i-1][j+1] == '@') total_alive += 1;

					//Right-Down
					if ((*current)[i+1][j+1] == '@') total_alive += 1;

					//Update cell
					if((*current)[i][j] == '@' && total_alive == 2){
						(*next)[i][j] = '@';
					}
					else if(total_alive == 3){
						(*next)[i][j] = '@';
					}
					else{
						(*next)[i][j] = ' ';
					}
				}
			}

			// Set buffer
			for (i = 0; i<current->size(); i++){
				(*next)[i][0] = (*next)[i][(*next)[0].size()-2];
				(*next)[i][(*next)[0].size()-1] = (*current)[i][1];
			}

			for (j = 0; j<(*current)[0].size(); j++){
				(*next)[0][j]=(*current)[(*current).size()-2][j];
				(*next)[current->size()-1][j]=(*current)[1][j];
			}
			swap(current,next);

		}

		void run(){
			while(true){
				system("clear");
				print();
				tick();
				usleep(70000);

			}

		}

		void gui_run(){
			GUI_Board gui = GUI_Board();
			while(gui.running){
				gui_print(gui);
				tick();
				gui.input_manager();
				usleep(70000);
			}
			gui.destroy();
		}


	private:
		board_vector* current;
		board_vector* next;
};





int main(int argc, char* args[]){
	Life_Board board = Life_Board(42,32);
	board.gui_run();
}
