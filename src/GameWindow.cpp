#include "GameEngine/GameWindow.h"

int GameWindow::windowCount;

GameWindow::GameWindow(int w, int h, std::string title){
	if(0 == GameWindow::windowCount){
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
		
	}

	window = SDL_CreateWindow(
        		title.c_str(),                  
        		SDL_WINDOWPOS_CENTERED,           
        		SDL_WINDOWPOS_CENTERED,           
        		w,                               
        		h,                               
        		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE               
   			 );

	if (window == NULL) {
      		// In the case that the window could not be made...
       		printf("Could not create window: %s\n", SDL_GetError());
        	return;
    	}	
	
	glContext = SDL_GL_CreateContext(window);

	GameWindow::windowCount++;

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

}

GameWindow::~GameWindow(){
	SDL_DestroyWindow(window);
}


int GameWindow::getWindowWidth(){
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	
	return w;
}

int GameWindow::getWindowHeight(){
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);
	
	return h;
}
