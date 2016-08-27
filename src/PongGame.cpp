#include "PongGame.h"
#include <sstream>

const int WIDTH = 900;
const int HEIGHT = 600;

const int BALL_STARTX = 450;
const int BALL_STARTY = 300;

PongGame::PongGame()
:Game(WIDTH, HEIGHT, "Pong"){
	startTime = -1;
	countdown = 5;	

	winner = "";
	
	currentState = MENU_STATE;
	GameEngine::setBackgroundColor(0.8f, 0.9f, 1.0f);
	hud = new PongHUD();
	paddle = new PongPaddle(100, 300, 50, 200);
	paddle2 = new PongPaddle2(750, 100, 50, 200);
	ball = new PongBall(BALL_STARTX, BALL_STARTY, 50, 50);
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
	case COUNTDOWN_STATE:
		runCountdownState();
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
		currentState = COUNTDOWN_STATE;
	}
}

void PongGame::runCountdownState(){
	ball->draw();
	paddle->draw();
	paddle->update();
	paddle2->draw();
	paddle2->update();	
	base1->draw();
	base2->draw();
	GameEngine::setColor(0.0f, 0.0f, 0.0f);
	GameEngine::drawText("GAME     STARTING     IN:", 150, 400, 1.5f);

	if(-1 == startTime){ startTime = clock(); }
	if(clock() - startTime >= CLOCKS_PER_SEC){ 
		countdown--;
		startTime = clock();
	}
	
	std::stringstream cd;
	cd << countdown;
	GameEngine::drawText(cd.str(), 400, 200, 2.5f);

	if(countdown <= 0){ 
		currentState = GAME_STATE; 
		countdown = 5;
		startTime = -1;	
	}

}

void PongGame::runGameState(){
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

	if(base1->getCurrentStatus() <= 0){
		winner = "Player      2";
		currentState = END_STATE;
	}else if(base2->getCurrentStatus() <= 0){
		winner = "Player      1";
		currentState = END_STATE;
	}
}

void PongGame::runEndState(){
	GameEngine::setColor(0, 0, 0);
	GameEngine::drawText("GAME   OVER!", 100, 400, 3.0f);
	GameEngine::drawText(winner + "       Wins!", 150, 290, 2.0f);
	GameEngine::drawText("Press BACK to Restart", 250, 200, 1.0f);

	if(GameEngine::GAMEPAD1_BACK || GameEngine::GAMEPAD2_BACK){
		resetGame();
		currentState = COUNTDOWN_STATE;
	}
}

void PongGame::resetGame(){
	base1->setCurrentStatus(base1->getMaxStatus());
	base2->setCurrentStatus(base2->getMaxStatus());
	ball->reset(BALL_STARTX, BALL_STARTY);
}







