#pragma once

#include "SDL2/SDL.h"
#include "GameEngine/GameWindow.h"

class GameEngine{
public:
	virtual ~GameEngine();

	static GameEngine* getInstance();
	void startGame();
	void stopGame();

private:
	GameEngine();
	int gameCounter;

	GameWindow* window;

static GameEngine* gameEngineInstance;
};
