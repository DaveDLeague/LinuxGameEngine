#pragma once

#include <stdlib.h>
#include <string>
#include <ctime>
#include "GameEngine/Game.h"
#include "PongHUD.h"
#include "PongPaddle.h"
#include "PongPaddle2.h"
#include "PongBall.h"
#include "PongBase.h"
#include "PongBase2.h"

class PongGame: public Game{
public:
	PongGame();
	virtual ~PongGame();

	void update();

private:
	enum GameStates {
						MENU_STATE,
						COUNTDOWN_STATE,
						GAME_STATE,
						END_STATE,
						TOTAL_GAME_STATES
					};	
	int currentState;

	int countdown;

	std::string winner;

	void runMenuState();
	void runCountdownState();
	void runGameState();
	void runEndState();
	void resetGame();

	PongHUD* hud;
	PongPaddle* paddle;
	PongPaddle2* paddle2;
	PongBall* ball;
	PongBase* base1;
	PongBase2* base2;

	clock_t startTime;
};
