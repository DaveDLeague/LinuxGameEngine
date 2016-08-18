
#include "GameEngine/GameEngine.h"
#include "PongGame.h"

int main(){
	PongGame* g = new PongGame();
	
	GameEngine::getInstance()->loadGame(g);
	GameEngine::getInstance()->startGame();

	delete g;

	return 0;
}
