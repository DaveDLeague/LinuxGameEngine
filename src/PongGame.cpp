#include "PongGame.h"

const int WIDTH = 900;
const int HEIGHT = 600;

PongGame::PongGame()
:Game(WIDTH, HEIGHT, "Pong"){
	currentState = MENU_STATE;
	GameEngine::setBackgroundColor(0.8f, 0.9f, 1.0f);
	paddle = new PongPaddle(100, 300, 50, 200);
	ball = new PongBall(500, 300, 50, 50);
	p1Meter = new StatusMeter(50, 500, 200, 50);
	base1 = new PongBase(0, 0, 25, HEIGHT);

	GameEngine::loadFont("blink", "../LinuxGameEngine/res/fonts/Blink.otf");
	GameEngine::setFont("blink");
}

PongGame::~PongGame(){
	delete paddle;
	delete ball;
	delete p1Meter;
	delete base1;
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
	ball->checkCollision(paddle);
	ball->checkCollision(base1);
	paddle->draw();
	ball->draw();
	p1Meter->draw();
	base1->draw();
	if(keys[GameEngine::SPACE_KEY]){
		//currentState = MENU_STATE;
		p1Meter->incrementCurrentStatus(-1);
	}
}

void PongGame::runEndState(){

}
