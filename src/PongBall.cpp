#include "PongBall.h"

const int SPEED = 10;

PongBall::PongBall(int x, int y, int w, int h)
:GameObject(x, y, w, h){
	init();
}

PongBall::~PongBall(){
	delete cbox;
}

void PongBall::update(){
	cbox->update(x + xspeed, y + yspeed, w, h);	
	
	if(cbox->isColliding()){
		xspeed = -xspeed;
		cbox->update(x + xspeed, y + yspeed, w, h);
	}else{
		x += xspeed;
		y += yspeed;
	}

	if(x <= 0 || x >= GameEngine::getInstance()->getWindowWidth() - w){ 
		xspeed = -xspeed; 
	}
	if(y <= 0 || y >= GameEngine::getInstance()->getWindowHeight() - h){
		yspeed = -yspeed;
	}
}

void PongBall::draw(){
	GameEngine::getInstance()->getRenderer()->setColor(1.0f, 0.0f, 0.0f);
	GameEngine::getInstance()->getRenderer()->fillOval(x, y, w, h);
}

void PongBall::checkCollision(GameObject o){
	cbox->checkCollision(o);
}

void PongBall::init(){
	cbox = new CollisionBox(x, y, w, h);
	xspeed = SPEED;
	yspeed = SPEED;
}
