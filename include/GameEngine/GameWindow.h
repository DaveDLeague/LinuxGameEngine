#pragma once

#include <string>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GL/gl.h"

#include "GameEngine/Game.h"

class GameWindow{
public:
	GameWindow(int w, int h, std::string title);
	virtual ~GameWindow();
	
	void refresh();
	void setVisible(bool v);
	void setBackgroundColor(float r, float g, float b);
	void setWindowWidth(int w);
	void setWindowHeight(int h);
	void setWindowSize(int w, int h);
	void setWindowTitle(std::string t);
	void centerWindow();
	int getWindowWidth();
	int getWindowHeight();
	std::string getWindowTitle();

private:
	SDL_Window* window;
	SDL_GLContext glContext;
};
