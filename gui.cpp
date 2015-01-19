#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <zlib.h>
#include "gui.h"
#include <vector>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MENU_HEIGHT = 40;


GUI_Board::GUI_Board(){
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );

	} else {

		//Create Window
		window = SDL_CreateWindow( "C'est la vie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT + MENU_HEIGHT, SDL_WINDOW_SHOWN );

		if ( window == NULL){
			printf( "window could not be created! SDL_Error: %s\n", SDL_GetError() );
		} else {

			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			SDL_SetRenderDrawColor( renderer,0xFF , 0xFF, 0xFF, 0xFF );
			SDL_RenderClear(renderer);

			SDL_Surface* tmp = IMG_Load("./circle.png");
			if(!tmp){
				printf("PNG didn't load\n");
			}


			texture = SDL_CreateTextureFromSurface(renderer, tmp);
			if (!texture){
				printf(SDL_GetError());
			}


			SDL_SetRenderDrawColor( renderer,0, 0, 0, 0xFF );


		}
	}

	running = true;
	pause = false;
	reinstanciate = false;
	
}

void GUI_Board::draw_circle(int x, int y){
	SDL_SetRenderDrawColor( renderer,0, 0, 0, 0xFF );
	const int NUM_X_LINES = 40;
	const int NUM_Y_LINES = 30;
	const int X_SPACING = SCREEN_WIDTH/NUM_X_LINES;
	const int Y_SPACING = SCREEN_HEIGHT/NUM_Y_LINES;
	const int off = 1;

	SDL_Rect renderQuad = { (X_SPACING * x) + off, Y_SPACING * y + off, 15, 15 };
	SDL_RenderCopy( renderer, texture, NULL, &renderQuad	);
}


void GUI_Board::draw_grid(){
	SDL_SetRenderDrawColor( renderer,0, 0, 0, 0xFF );
	const int NUM_X_LINES = 40;
	const int NUM_Y_LINES = 30;
	const int X_SPACING = SCREEN_WIDTH/NUM_X_LINES;
	const int Y_SPACING = SCREEN_HEIGHT/NUM_Y_LINES;
	int i;


	for ( i = 1; i < NUM_X_LINES; i++ ){
		SDL_RenderDrawLine(renderer, i * X_SPACING, 0, i * X_SPACING, SCREEN_HEIGHT);
	}

	for ( i = 1; i < NUM_Y_LINES; i++ ){
		SDL_RenderDrawLine(renderer, 0, i * Y_SPACING, SCREEN_WIDTH, i * Y_SPACING);
	}

}

void GUI_Board::update(){

	draw_grid();
	init_menu();
	SDL_RenderPresent( renderer );
}

void GUI_Board::clear(){
	SDL_SetRenderDrawColor( renderer,0xFF , 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
}

void GUI_Board::destroy(){
	SDL_DestroyWindow( window );
	SDL_Quit();
}

void GUI_Board::input_manager(){
	while(SDL_PollEvent(&events)) {
		if(events.type == SDL_QUIT)
			running = false;
		if(events.type == SDL_MOUSEBUTTONDOWN){
			int x, y;
			x = events.motion.x;
			y = events.motion.y;
			printf("clicked @ %d %d\n", events.motion.x, events.motion.y);
			if ( y > SCREEN_HEIGHT && x > 10 && x < 50 ){
				printf("play\n");
				pause = false;
			}
			if ( y > SCREEN_HEIGHT && x > 50 && x < 90 ){
				printf("pause\n");
				pause = true;
			}
			if ( y > SCREEN_HEIGHT && x > 90 && x < 130 ){
				printf("restart\n");
				reinstanciate = true;
			}
		}
	}
}

void GUI_Board::init_menu(){

	vector<char*> pngs; 
	pngs.push_back("./play.png");
	pngs.push_back("./pause.png");
	pngs.push_back("./restart.png");

	int i;


	for ( i = 0; i < pngs.size(); i++ ){
		SDL_Surface* tmp = IMG_Load(pngs[i]);
		if(!tmp){
			printf("PNG didn't load\n");
		}


		SDL_Texture* tmp_texture = SDL_CreateTextureFromSurface(renderer, tmp);
		if (!tmp_texture){
			printf(SDL_GetError());
		}

		SDL_Rect renderQuad = {10 + 40 * i, SCREEN_HEIGHT, 35, 35};
		SDL_RenderCopy( renderer, tmp_texture, NULL, &renderQuad	);

	}
}




