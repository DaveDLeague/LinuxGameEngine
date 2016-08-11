#include "PongBall.h"

PongBall::PongBall(int x, int y, int w, int h)
:GameObject(x, y, w, h){
	init();
}

PongBall::PongBall(int x, int y, int w, int h, int r, int g, int b)
:GameObject(x, y, w, h, r, g, b){
	init();
}

PongBall::PongBall(int x, int y, int w, int h, float r, float g, float b)
:GameObject(x, y, w, h, r, g, b){
	init();
}	

void PongBall::update(){
	x += xspeed;
	y += yspeed;

	if(x <= 0 || x >= GameEngine::getInstance()->getWindowWidth() - w){ 
		xspeed = -xspeed; 

		if(xspeed > 0){ xspeed++; }
	}
	if(y <= 0 || y >= GameEngine::getInstance()->getWindowHeight() - h){
		yspeed = -yspeed;
		
		if(yspeed > 0){ yspeed++; }
	}
	
}

void PongBall::draw(Renderer* r){
	r->setColor(1.0f, 0.0f, 0.0f);
	r->fillOval(x, y, w, h);
}

void PongBall::init(){
	xspeed = 6;
	yspeed = 6;
}
