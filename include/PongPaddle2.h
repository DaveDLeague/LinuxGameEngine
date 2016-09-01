#pragma once

#include "PongPaddle.h"

class PongPaddle2: public PongPaddle{
public:
	PongPaddle2(int x, int y, int w, int h);
	
	virtual void draw();
	virtual void update();
private:

};
