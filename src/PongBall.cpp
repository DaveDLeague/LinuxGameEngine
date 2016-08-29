#include "PongBall.h"
#include "PongBase.h"
const int SPEED = 10;
const double PI = 3.1415926535897;

PongBall::PongBall(int x, int y, int w, int h)
:GameObject(x, y, w, h){
	init();
}

PongBall::~PongBall(){
	delete cbox;
	delete a1;
}

void PongBall::update(){
	nextX = x + (speed * sin(angle));
	nextY = y + (speed * cos(angle));
	cbox->update(nextX, nextY, w, h);

	if((nextY + h) >= GameEngine::getWindowHeight() || nextY < 0){
		angle = PI - angle;
		GameEngine::playSoundEffect("bonk");
	}
	
	x = nextX;
	y = nextY;

	if(x < 0) { x = 0; }
	else if(x + w > GameEngine::getWindowWidth()) { x = GameEngine::getWindowWidth() - w; }
	if(y < 0) { y = 0; }
	else if(y + h > GameEngine::getWindowHeight()) { y = GameEngine::getWindowHeight() - h; }
	if(angle < 0.1f && angle > -0.1f){
		angle = 0.2f;
	}

	if(-1 == speedTimer){ speedTimer = clock(); }
	if(clock() - speedTimer >= CLOCKS_PER_SEC * 10){ 
		speed ++;
		speedTimer = clock(); 
	}
	animator->update();
}

void PongBall::draw(){
	//GameEngine::setColor(1.0f, 0.0f, 0.0f);
	//GameEngine::fillOval(x, y, w, h);
	GameEngine::drawImage(animator->getCurrentImage(), x, y, w, h);
}

void PongBall::checkCollision(GameObject* o){
	cbox->checkCollision(*o);

	if(cbox->isColliding()){
		int cx = x + (w / 2);
		int cy = y + (h / 2);
		int ocx = o->getX() + (o->getWidth() / 2);
		int ocy = o->getY() + (o->getHeight() / 2);
	
		if(o->getTag().compare("paddle") == 0){ 
			angle = (PI / 2) - (atan2((cy - ocy), (cx - ocx)));
			GameEngine::playSoundEffect("tock");
			animator->setAnimation("a2");
		}else if(o->getTag().compare("base") == 0){ 
			PongBase *b = static_cast<PongBase*>(o);			
			angle = (2 * PI) - angle;
			x += (speed * sin(angle));
			y += (speed * cos(angle));
			b->registerHit();
			b = NULL;
			GameEngine::playSoundEffect("smash");
			animator->setAnimation("a1");
		}
	}
}

void PongBall::reset(int x, int y){
	this->x = x;
	this->y = y;

	speed = SPEED;
}

void PongBall::init(){
	tag = "ball";
	cbox = new CollisionBox(x, y, w, h);
	angle = PI / 4;
	speed = SPEED;
	
	speedTimer = -1;

	nextX = x;
	nextY = y;

	srand (time(NULL));	

	animator = new Animator();
	a1 = new Animation(2);
	a2 = new Animation();
	a1->loadImage("../LinuxGameEngine/res/planet.png");
	a1->loadImage("../LinuxGameEngine/res/dice.png");

	a2->loadImage("../LinuxGameEngine/res/land.jpg");	
	animator->loadAnimation("a1", a1);
	animator->loadAnimation("a2", a2);
	GameEngine::loadSoundEffect("bonk", "../LinuxGameEngine/res/sounds/sound.wav");
	GameEngine::loadSoundEffect("tock", "../LinuxGameEngine/res/sounds/tock.wav");
	GameEngine::loadSoundEffect("smash", "../LinuxGameEngine/res/sounds/base_hit.wav");
}
