#pragma once

#include "PongBase.h"

class PongBase2: public PongBase{
public:
	PongBase2(int x, int y, int w, int h);
	virtual void draw();
	virtual void registerHit();
	void setCurrentStatus(int s);
	void setMaxStatus(int m);
private:
};
