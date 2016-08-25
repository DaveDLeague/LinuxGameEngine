#include "PongGame.h"

PongGame::PongGame()
:Game(900, 600, "Pong"){
	currentState = MENU_STATE;
	GameEngine::setBackgroundColor(0.8f, 0.9f, 1.0f);
	paddle = new PongPaddle(100, 300, 50, 200);
	ball = new PongBall(500, 300, 50, 50);
	GameEngine::loadFont("blink", "../LinuxGameEngine/res/fonts/Blink.otf");
	GameEngine::setFont("blink");
}

PongGame::~PongGame(){
	delete paddle;
	delete ball;
}

void PongGame::update(){
	switch(currentState){
	case MENU_STATE:
		runMenuState();
		break;
	case GAME_STATE:
		runGameState();
		break;
	case END_STATE:
		runEndState();
		break;
	default:
		runMenuState();
	}
}

void PongGame::runMenuState(){
	const Uint8* keys = GameEngine::getKeyState();

	GameEngine::setColor(0, 0, 0);
	GameEngine::drawText("PARTY   PONG!", 50, 400, 3.0f);

	if(keys[GameEngine::ENTER_KEY]){
		currentState = GAME_STATE;
	}
}

void PongGame::runGameState(){
	const Uint8* keys = GameEngine::getKeyState();
	paddle->update();
	ball->update();
	ball->checkCollision(*paddle);
	paddle->draw();
	ball->draw();

	if(keys[GameEngine::SPACE_KEY]){
		currentState = MENU_STATE;
	}
}

void PongGame::runEndState(){

}
