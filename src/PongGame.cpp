#include "PongGame.h"

PongGame::PongGame()
:Game(900, 600, "Pong"){
	paddle = new PongPaddle(100, 300, 50, 200);
	ball = new PongBall(200, 300, 50, 50);

	GameEngine::getInstance()->getRenderer()->loadTexture("fart", "../LinuxGameEngine/res/planet.png", true);
	GameEngine::getInstance()->getRenderer()->loadTexture("fart2", "../LinuxGameEngine/res/dice.png", true);
}

PongGame::~PongGame(){
	delete paddle;
	delete ball;
}

void PongGame::update(){
	
	paddle->update();
	ball->update();
	ball->checkCollision(*paddle);
	paddle->draw();
	ball->draw();
	GameEngine::getInstance()->getRenderer()->setColor(255, 255, 0);
	GameEngine::getInstance()->getRenderer()->drawText("TEST", 10, 10);
	GameEngine::getInstance()->getRenderer()->drawImage("fart", 100, 100, 100, 100);
	GameEngine::getInstance()->getRenderer()->drawImage("fart2", 400, 400, 100, 100);
}
