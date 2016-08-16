#include "PongPaddle.h"

PongPaddle::PongPaddle(int x, int y, int w, int h)
:GameObject(x, y, w, h){
	init();
}

PongPaddle::PongPaddle(int x, int y, int w, int h, int r, int g, int b)
:GameObject(x, y, w, h, r, g, b){
	init();
}

PongPaddle::PongPaddle(int x, int y, int w, int h, float r, float g, float b)
:GameObject(x, y, w, h, r, g, b){
	init();
}	

PongPaddle::~PongPaddle(){
	delete cbox;
}

void PongPaddle::update(){
	const Uint8* keys = GameEngine::getInstance()->getKeyState();

	cbox->update(x, y, w, h);

	if(keys[GameEngine::UP_KEY] || keys[GameEngine::W_KEY]){
		y += speed;	
	}
	if(keys[GameEngine::DOWN_KEY] || keys[GameEngine::S_KEY]){
		y -= speed;	
	}

	if(y <= 0){ y = 0; }
	if(y >= GameEngine::getInstance()->getWindowHeight() - h){
		y = GameEngine::getInstance()->getWindowHeight() - h;
	}
}

void PongPaddle::draw(Renderer* r){
	r->setColor(0.0f, 0.0f, 1.0f);
	//r->fillRect(x, y, w, h);
	r->drawImage(x, y, w, h);
}

void PongPaddle::init(){
	cbox = new CollisionBox(x, y, w, h);
	speed = 6;
}
