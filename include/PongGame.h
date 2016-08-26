#pragma once

#include "GameEngine/Game.h"
//#include "StatusMeter.h"
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
						GAME_STATE,
						END_STATE,
						TOTAL_GAME_STATES
					};	
	int currentState;

	void runMenuState();
	void runGameState();
	void runEndState();

	PongHUD* hud;
	PongPaddle* paddle;
	PongPaddle2* paddle2;
	PongBall* ball;
	//StatusMeter* p1Meter;
	PongBase* base1;
	PongBase2* base2;
};
