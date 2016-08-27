#include "PongPaddle2.h"

PongPaddle2::PongPaddle2(int x, int y, int w, int h):
PongPaddle(x, y, w, h){

}

void PongPaddle2::update(){
	const Uint8* keys = GameEngine::getKeyState();

	cbox->update(x, y, w, h);

	if(keys[GameEngine::UP_KEY]){
		y += speed;	
	}
	if(keys[GameEngine::DOWN_KEY]){
		y -= speed;	
	}

	y += speed * -GameEngine::GAMEPAD2_AXIS_LEFT_Y;

	if(y <= 0){ y = 0; }
	if(y >= GameEngine::getWindowHeight() - h){
		y = GameEngine::getWindowHeight() - h;
	}
}

void PongPaddle2::draw(){
	GameEngine::setColor(0.0f, 1.0f, 1.0f);
	GameEngine::fillRect(x, y, w, h);
	//GameEngine::drawImage("planet", x, y, w, h);
}

