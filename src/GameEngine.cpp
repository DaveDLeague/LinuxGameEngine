
#include "GameEngine/GameEngine.h"

GameEngine* GameEngine::gameEngineInstance;

GameEngine::GameEngine() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gameCounter = 0;
	window = NULL;
}

GameEngine::~GameEngine() {
	delete window;
	delete gameEngineInstance;
}

GameEngine* GameEngine::getInstance() {

	if (!gameEngineInstance) {
		gameEngineInstance = new GameEngine();
	}
	return gameEngineInstance;
}

void GameEngine::startGame() {
	window = new GameWindow(900, 700, "PONG");
}
