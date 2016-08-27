#include "PongPaddle.h"

PongPaddle::PongPaddle(int x, int y, int w, int h)
:GameObject(x, y, w, h){
	init();
}


PongPaddle::~PongPaddle(){
	delete cbox;
}

void PongPaddle::update(){
	const Uint8* keys = GameEngine::getKeyState();

	cbox->update(x, y, w, h);

	if(keys[GameEngine::W_KEY]){
		y += speed;	
	}
	if(keys[GameEngine::S_KEY]){
		y -= speed;	
	}

	y += speed * -GameEngine::GAMEPAD1_AXIS_LEFT_Y;

	if(y <= 0){ y = 0; }
	if(y >= GameEngine::getWindowHeight() - h){
		y = GameEngine::getWindowHeight() - h;
	}

}

void PongPaddle::draw(){
	GameEngine::setColor(0.0f, 0.0f, 1.0f);
	GameEngine::fillRect(x, y, w, h);
	//GameEngine::drawImage("planet", x, y, w, h);
}

void PongPaddle::init(){
	tag = "paddle";
	
	cbox = new CollisionBox(x, y, w, h);
	speed = 10;

	//GameEngine::getInstance()->getRenderer()->loadImage("planet", "../LinuxGameEngine/res/planet.png", false);
}
