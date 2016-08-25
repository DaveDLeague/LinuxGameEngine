#include "StatusMeter.h"

StatusMeter::StatusMeter(int x, int y, int w, int h):
GameObject(x, y, w, h){
	init();
}

StatusMeter::~StatusMeter(){

}

void StatusMeter::draw(){
	GameEngine::setColor(1.0f, 0.0f, 0.5f);
	float nw = ((float)currentStatus / (float)maxStatus) * (float)w;
	GameEngine::fillRect(x, y, (int)nw, h);
	GameEngine::setColor(0.0f, 0.0f, 0.0f);	
	GameEngine::drawRect(x, y, w, h);
}

void StatusMeter::init(){
	maxStatus = 10;
	currentStatus = 10;
}
