#include "PongGame.h"

PongGame::PongGame()
:Game(900, 600, "Pong"){
	paddle = new PongPaddle(100, 300, 50, 200);
	ball = new PongBall(200, 300, 50, 50);
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

	GameEngine::getInstance()->getRenderer()->drawText("TEST", 10, 10);
}
