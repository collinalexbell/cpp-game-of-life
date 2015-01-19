all: gui term

gui: gui_main.cpp
	g++ -w -lSDL2 -lSDL2_image gui.cpp game.cpp gui_main.cpp -o ./bin/life_gui

term: term_main.cpp
	g++ -w -lSDL2 -lSDL2_image gui.cpp game.cpp term_main.cpp -o ./bin/life_term
