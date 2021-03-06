#include "PongBase.h"

PongBase::PongBase(int x, int y, int w, int h):
GameObject(x, y, w, h){
	init();
}

PongBase::~PongBase(){

}

void PongBase::draw(){
	//GameEngine::setColor(0.0f, 0.0f, 0.75f);
	//GameEngine::fillRect(x, y, w, h);
	GameEngine::drawImage("ice", x, y, w, h);
}

void PongBase::registerHit(){
	currentStatus -= 1;
	hud->setP1CurrentStatus(currentStatus);
}

void PongBase::init(){
	tag = "base";

	maxStatus = 10;
	currentStatus = maxStatus;
	GameEngine::loadImage("ice", "../LinuxGameEngine/res/ice.jpg", false);
}

void PongBase::setCurrentStatus(int s){
	currentStatus = s;
	hud->setP1CurrentStatus(currentStatus);
}

void PongBase::setMaxStatus(int m){
	maxStatus = m;
	hud->setP1MaxStatus(maxStatus);
}
