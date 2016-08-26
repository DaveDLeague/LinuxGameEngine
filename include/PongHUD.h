#pragma once

#include "GameEngine/GameEngine.h"
#include "StatusMeter.h"

class PongHUD{
public:
	PongHUD();
	virtual ~PongHUD();

	virtual void update();
	virtual void draw();

	void setP1MaxStatus(int m);
	void setP1CurrentStatus(int c);
	void setP2MaxStatus(int m);
	void setP2CurrentStatus(int c);
	
private:
	int p1Max;
	int p1Current;
	int p2Max;
	int p2Current;

	StatusMeter* p1Meter;
	StatusMeter* p2Meter;
};
