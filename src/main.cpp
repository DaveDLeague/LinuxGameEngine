#include "GameEngine/GameEngine.h"
#include "PongGame.h"
#include <iostream>
#include <ctime>

int main(){
	PongGame g;
	GameEngine::getInstance()->loadGame(&g);
	GameEngine::getInstance()->startGame();
	
	return 0;
}

