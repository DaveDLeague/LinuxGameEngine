#include "PongBase.h"

PongBase::PongBase(int x, int y, int w, int h):
GameObject(x, y, w, h){
	init();
}

PongBase::~PongBase(){

}

void PongBase::draw(){
	GameEngine::setColor(0.0f, 0.0f, 0.75f);
	GameEngine::fillRect(x, y, w, h);
}

void PongBase::registerHit(){
	std::cout << "OUCH!!!\n";
}

void PongBase::init(){
	tag = "base";
}