#include "PongBase2.h"

PongBase2::PongBase2(int x, int y, int w, int h):
PongBase(x, y, w, h){
	init();
}

void PongBase2::draw(){
	GameEngine::setColor(0.0f, 0.75f, 0.0f);
	GameEngine::fillRect(x, y, w, h);
}

void PongBase2::registerHit(){
	currentStatus -= 1;
	hud->setP2CurrentStatus(currentStatus);
}

void PongBase2::setCurrentStatus(int s){
	currentStatus = s;
	hud->setP2CurrentStatus(currentStatus);
}

void PongBase2::setMaxStatus(int m){
	maxStatus = m;
	hud->setP2MaxStatus(maxStatus);
}
