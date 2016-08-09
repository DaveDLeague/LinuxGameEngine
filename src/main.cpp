
#include "GameEngine/GameEngine.h"

int main(){
	/*SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_CENTERED,           // initial x position
        SDL_WINDOWPOS_CENTERED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

	if (window == NULL) {
      		// In the case that the window could not be made...
       		printf("Could not create window: %s\n", SDL_GetError());
        	return 1;
    	}	

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	bool quit = false;
    	while(!quit){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			 //User requests quit
                	if( event.type == SDL_QUIT )
                	{
                	    quit = true;
               		}
		}

		glClearColor(0,0,1,1);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

    	// Close and destroy the window
    	SDL_DestroyWindow(window);

    	// Clean up
    	SDL_Quit();*/

	GameEngine::getInstance()->startGame();

	return 0;
}
