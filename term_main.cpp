#include "game.h"
#include <string>

int main(int argc, char* args[]){
  int secs = -1;
	Life_Board board = Life_Board(50,50);
  if(argc > 1) {
    secs = stoi(args[1]);
    board.run(secs);
  } else {
    board.run();
  }
}

