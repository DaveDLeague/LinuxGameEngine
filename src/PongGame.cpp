#include "PongGame.h"

const int WIDTH = 900;
const int HEIGHT = 600;

PongGame::PongGame()
:Game(WIDTH, HEIGHT, "Pong"){
	currentState = MENU_STATE;
	GameEngine::setBackgroundColor(0.8f, 0.9f, 1.0f);
	hud = new PongHUD();
	paddle = new PongPaddle(100, 300, 50, 200);
	paddle2 = new PongPaddle2(750, 300, 50, 200);
	ball = new PongBall(500, 300, 50, 50);
	base1 = new PongBase(0, 0, 25, HEIGHT);
	base2 = new PongBase2(WIDTH - 25, 0, 25, HEIGHT);
	
	base1->setHUD(hud);
	base2->setHUD(hud);

	GameEngine::loadFont("blink", "../LinuxGameEngine/res/fonts/Blink.otf");
	GameEngine::setFont("blink");
}

PongGame::~PongGame(){
	delete hud;
	delete paddle;
	delete paddle2;
	delete ball;
	delete base1;
	delete base2;
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

	if(keys[GameEngine::ENTER_KEY] || GameEngine::GAMEPAD1_START){
		currentState = GAME_STATE;
	}
}

void PongGame::runGameState(){
	const Uint8* keys = GameEngine::getKeyState();
	paddle->update();
	paddle2->update();
	ball->update();
	ball->checkCollision(paddle);
	ball->checkCollision(paddle2);
	ball->checkCollision(base1);
	ball->checkCollision(base2);
	paddle->draw();
	paddle2->draw();
	ball->draw();
	base1->draw();
	base2->draw();
	hud->draw();

	if((base1->getCurrentStatus() <= 0) || (base2->getCurrentStatus() <= 0)){
		currentState = MENU_STATE;
	}
}

void PongGame::runEndState(){

}
