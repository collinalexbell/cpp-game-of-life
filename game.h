#ifndef GAME_H
#define GAME_H

#include <vector>
#include "gui.h"

using namespace std;

typedef vector<vector<char> > board_vector;

class Life_Board{
	public:
		Life_Board(int, int);
		void print();
		void gui_print(GUI_Board);
		void tick();
		void run();
		void gui_run();
		void reinstanciate();

	private:
		board_vector* current;
		board_vector* next;
};

#endif

