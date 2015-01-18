#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <zlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void draw_grid(SDL_Renderer*);
void draw_circle(int, int, SDL_Renderer*, SDL_Texture*);
	
int main( int argc, char* args[] ){
	SDL_Window* window = NULL;

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );

	} else {

		//Create Window
		window = SDL_CreateWindow( "C'est la vie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if ( window == NULL){
			printf( "window could not be created! SDL_Error: %s\n", SDL_GetError() );
		} else {
			
			SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			SDL_SetRenderDrawColor( renderer,0xFF , 0xFF, 0xFF, 0xFF );
			SDL_RenderClear(renderer);

			SDL_Surface* tmp = IMG_Load("./circle.png");
			if(!tmp){
				printf("PNG didn't load\n");
			}


			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmp);
			if (!texture){
				printf(SDL_GetError());
			}


			SDL_SetRenderDrawColor( renderer,0, 0, 0, 0xFF );

			

			draw_circle(39,29,renderer, texture);
			draw_circle(30,20,renderer, texture);
			draw_circle(20,10,renderer, texture);


			draw_grid(renderer);
			SDL_RenderPresent( renderer );

			SDL_Delay( 5000 );
		}
	}
	SDL_DestroyWindow( window );
}

void draw_grid(SDL_Renderer* renderer){
	SDL_SetRenderDrawColor( renderer,0, 0, 0, 0xFF );
	const int NUM_X_LINES = 40;
	const int NUM_Y_LINES = 30;
	const int X_SPACING = SCREEN_WIDTH/NUM_X_LINES;
	const int Y_SPACING = SCREEN_HEIGHT/NUM_Y_LINES;
	int i;


	for ( i = 1; i < NUM_X_LINES; i++ ){
		SDL_RenderDrawLine(renderer, i * X_SPACING, 0, i * X_SPACING, SCREEN_HEIGHT);
	}

	for ( i = 1; i < NUM_X_LINES; i++ ){
		SDL_RenderDrawLine(renderer, 0, i * Y_SPACING, SCREEN_WIDTH, i * Y_SPACING);
	}

}

void draw_circle(int x, int y, SDL_Renderer* renderer, SDL_Texture* texture){
	const int NUM_X_LINES = 40;
	const int NUM_Y_LINES = 30;
	const int X_SPACING = SCREEN_WIDTH/NUM_X_LINES;
	const int Y_SPACING = SCREEN_HEIGHT/NUM_Y_LINES;
	const int off = 1;

	SDL_Rect renderQuad = { (X_SPACING * x) + off, Y_SPACING * y + off, 15, 15 };
	SDL_RenderCopy( renderer, texture, NULL, &renderQuad	);

}
