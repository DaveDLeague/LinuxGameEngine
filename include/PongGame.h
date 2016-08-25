#pragma once

#include "GameEngine/Game.h"
#include "StatusMeter.h"
#include "PongPaddle.h"
#include "PongBall.h"
#include "PongBase.h"

class PongGame: public Game{
public:
	PongGame();
	virtual ~PongGame();

	void update();

private:
	enum GameStates {
						MENU_STATE,
						GAME_STATE,
						END_STATE,
						TOTAL_GAME_STATES
					};	
	int currentState;

	void runMenuState();
	void runGameState();
	void runEndState();

	PongPaddle* paddle;
	PongBall* ball;
	StatusMeter* p1Meter;
	PongBase* base1;
};
