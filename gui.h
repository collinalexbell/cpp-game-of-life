#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>

class GUI_Board{
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		SDL_Event events;

	public:
		bool running, pause, reinstanciate;
		GUI_Board();
		void draw_circle(int, int);
		void draw_grid();
		void update();
		void clear();
		void destroy();
		void input_manager();
		void init_menu();
		


};

#endif
