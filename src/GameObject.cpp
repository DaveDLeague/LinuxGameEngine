#include "GameEngine/GameObject.h"

GameObject::GameObject(int x, int y, int w, int h){
	init(x, y, w, h, 0, 0, 255);
}

GameObject::GameObject(int x, int y, int w, int h, int r = 0, int g = 0, int b = 255){
	init(x, y, w, h, r, g, b);
}

GameObject::GameObject(int x, int y, int w, int h, float r = 0.0f, float g = 0.0f, float b = 1.0f){
	init(x, y, w, h, (int)(r * 255.0f), (int)(g * 255.0f), (int)(b * 255.0f));
}

GameObject::~GameObject(){

}

int speed = 1;
void GameObject::update(){
	if(x >= 1000 || x <= 0){
		speed = -speed;
	} 

	if(y >= 1000 || y <= 0){
		speed = -speed;
	} 

	const Uint8* keys = GameEngine::getInstance()->getKeyState();

	if(keys[GameEngine::UP_KEY]){
		y += speed;
	}
}

void GameObject::draw(Renderer* ren){
	ren->setColor(r, g, b);
	ren->fillOval(x, y, w, h);
}

void GameObject::setColor(int r, int g, int b){
	this->r = r;
	this->g = g;
	this->b = b;
}

void GameObject::setColor(float r, float g, float b){
	this->r = (int)(r * 255.0f);
	this->g = (int)(g * 255.0f);
	this->b = (int)(b * 255.0f);
}

void GameObject::init(int x, int y, int w, int h, int r, int g, int b){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	this->g = g;
	this->b = b;
}
