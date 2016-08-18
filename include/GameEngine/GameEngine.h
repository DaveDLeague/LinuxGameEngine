#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GameEngine/Renderer.h"
#include "GameEngine/GameWindow.h"
#include "GameEngine/Game.h"

class GameEngine{
public:
	virtual ~GameEngine();

	static GameEngine* getInstance();
	void startGame();
	void stopGame();

	void loadGame(Game* game);
	
	int getWindowWidth();
	int getWindowHeight();

	const Uint8* getKeyState();

	const static int UP_KEY;
	const static int DOWN_KEY;
	const static int LEFT_KEY;
	const static int RIGHT_KEY;
	const static int W_KEY;
	const static int A_KEY;
	const static int S_KEY;
	const static int D_KEY;

	int getDeltaTime(){ return deltaTime; }

	Renderer* getRenderer(){ return renderer; }

private:
	float deltaTime;

	Game* currentGame;	

	Renderer* renderer;
	GameWindow* window;

	static GameEngine* gameEngineInstance;
	Uint8* keyState;	

	void initSDL();
	void initGameWindow();
	void initGLEW();
	void runGameLoop();

	GameEngine();

};
