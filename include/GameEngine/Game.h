#pragma once

#include <string>

#include "GameEngine/GameWindow.h"

class Game{
public:
	Game(){}
	Game(int w, int h, std::string t){
		width = w;
		height = h;
		title = t;
	}
	virtual ~Game(){}

	virtual void update() = 0;

	int getWidth(){ return width; }
	int getHeight(){ return height; }
	std::string getTitle(){ return title; }

protected:
	int width;
	int height;
	std::string title;

private:
};
