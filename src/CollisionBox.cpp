#include "GameEngine/CollisionBox.h"

CollisionBox::CollisionBox(int x, int y, int w, int h)
:GameObject(x, y, w, h){

}


void CollisionBox::checkCollision(GameObject o){
	int ox = o.getX();
	int oy = o.getY();
	int ow = o.getWidth();
	int oh = o.getHeight();

	if(ox < (x + w) && (ox + ow) > x &&
	   oy < (y + h) && (oy + oh) > y){
		collision = true;
	}else{
		collision = false;
	}

}

void CollisionBox::update(){

}

void CollisionBox::update(int x, int y, int w, int h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}


void CollisionBox::draw(Renderer* r){
	r->setColor(0, 255, 0);	
	r->fillRect(x, y, w, h);
}

void CollisionBox::init(){
	collision = false;
}


