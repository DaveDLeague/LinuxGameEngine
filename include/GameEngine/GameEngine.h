#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GameEngine/Renderer.h"
#include "GameEngine/GameWindow.h"

class GameEngine{
public:
	virtual ~GameEngine();

	static GameEngine* getInstance();
	void startGame();
	void stopGame();

private:
	GameEngine();

	Renderer* renderer;
	GameWindow* window;

	static GameEngine* gameEngineInstance;
};
