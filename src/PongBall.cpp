#include "PongBall.h"

const int SPEED = 0;

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

void PongBall::draw(Renderer* r){
	r->setColor(1.0f, 0.0f, 0.0f);
	r->fillOval(x, y, w, h);
}

void PongBall::checkCollision(GameObject o){
	cbox->checkCollision(o);
}

void PongBall::init(){
	cbox = new CollisionBox(x, y, w, h);
	xspeed = SPEED;
	yspeed = SPEED;
}
