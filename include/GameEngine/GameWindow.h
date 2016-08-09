#pragma once

#include <string>
#include "SDL2/SDL.h"
#include "GL/gl.h"

class GameWindow{
public:
	GameWindow(int w, int h, std::string title);
	virtual ~GameWindow();
	
	int getWindowWidth();
	int getWindowHeight();

private:
	SDL_Window* window;
	SDL_GLContext glContext;
	static int windowCount;
};
