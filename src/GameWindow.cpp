#include "GameEngine/GameWindow.h"

GameWindow::GameWindow(int w, int h, std::string title){
	
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
}

GameWindow::~GameWindow(){
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
}

void GameWindow::refresh(){
	
	SDL_GL_SwapWindow(window);
	
	glClear(GL_COLOR_BUFFER_BIT);
	
}

void GameWindow::setBackgroundColor(float r, float g, float b){
	glClearColor(r, g, b, 1.0);
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
