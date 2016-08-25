#include "GameEngine/GameObject.h"

GameObject::GameObject(int x, int y, int w, int h){
	init(x, y, w, h);
}

GameObject::~GameObject(){

}

void GameObject::update(){
	
}

void GameObject::draw(){

}

void GameObject::init(int x, int y, int w, int h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	tag = "";

}
