#include "PongBall.h"

const int SPEED = 10;
const double PI = 3.1415926535897;

PongBall::PongBall(int x, int y, int w, int h)
:GameObject(x, y, w, h){
	init();
}

PongBall::~PongBall(){
	delete cbox;
}

void PongBall::update(){
	nextX = x + (speed * sin(angle));
	nextY = y + (speed * cos(angle));
	cbox->update(nextX, nextY, w, h);
	
	if((nextX + w) >= GameEngine::getWindowWidth() || nextX < 0){
		angle = (2 * PI) - angle;
	}

	if((nextY + h) >= GameEngine::getWindowHeight() || nextY < 0){
		angle = PI - angle;
	}
	
	x = nextX;
	y = nextY;

	if(x < 0) { x = 0; }
	if(x + w > GameEngine::getWindowWidth()) { x = GameEngine::getWindowWidth() - w; }
	if(y < 0) { y = 0; }
	if(y + h > GameEngine::getWindowHeight()) { y = GameEngine::getWindowHeight() - h; }
}

void PongBall::draw(){
	GameEngine::setColor(1.0f, 0.0f, 0.0f);
	GameEngine::fillOval(x, y, w, h);
}

float spdflt = 0.0f;//DELET THIS SOON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void PongBall::checkCollision(GameObject o){
	cbox->checkCollision(o);

	int cx = x + (w / 2);
	int cy = y + (h / 2);
	int ocx = o.getX() + (o.getWidth() / 2);
	int ocy = o.getY() + (o.getHeight() / 2);

	if(cbox->isColliding()){
		angle = (PI / 2) - (atan2((cy - ocy), (cx - ocx)));
		spdflt += 0.1f;
		speed += spdflt;
	}
}

void PongBall::init(){
	cbox = new CollisionBox(x, y, w, h);
	angle = PI / 4;
	speed = SPEED;

	nextX = x;
	nextY = y;

	srand (time(NULL));	

	GameEngine::loadSoundEffect("bonk", "../LinuxGameEngine/res/sounds/sound.wav");
}
