#pragma once

#include "GameEngine/GameObject.h"

class PongBase: public GameObject{
public:
	PongBase(int x, int y, int w, int h);
	virtual ~PongBase();
	virtual void draw();
	virtual void registerHit();

private:
	void init();
};
