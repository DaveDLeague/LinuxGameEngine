#pragma once

#include "GameEngine/Game.h"
#include "PongPaddle.h"
#include "PongBall.h"

class PongGame: public Game{
public:
	PongGame();
	virtual ~PongGame();

	void update();

private:
	PongPaddle* paddle;
	PongBall* ball;
};
