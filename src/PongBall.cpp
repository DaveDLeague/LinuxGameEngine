#include "PongBall.h"
#include "PongBase.h"
const int SPEED = 10;
const double PI = 3.1415926535897;

PongBall::PongBall(int x, int y, int w, int h)
:GameObject(x, y, w, h){
	init();
}

PongBall::~PongBall(){
	p1 = NULL;
	p2 = NULL;
	delete cbox;
	delete fireA;
	delete iceA;
}

void PongBall::update(){
	switch(currentState){
		case GAME_START_STATE:
			runGameStartState();
			break;
		case BOUNCE_STATE:
			runBounceState();
			break;
		case CAUGHT_P1_STATE:
			runCaughtP1State();
			break;
		case CAUGHT_P2_STATE:
			runCaughtP2State();
			break;
	}
}

void PongBall::runGameStartState(){

}

void PongBall::runBounceState(){
	nextX = x + (speed * sin(angle));
	nextY = y + (speed * cos(angle));
	cbox->update(nextX, nextY, w, h);

	if((nextY + h) >= GameEngine::getCurrentGameHeight() || nextY < 0){
		angle = PI - angle;
		GameEngine::playSoundEffect("bonk");
	}
	
	x = nextX;
	y = nextY;

	if(x < 0) { x = 0; }
	else if(x + w > GameEngine::getCurrentGameWidth()) { x = GameEngine::getCurrentGameWidth() - w; }
	if(y < 0) { y = 0; }
	else if(y + h > GameEngine::getCurrentGameHeight()) { y = GameEngine::getCurrentGameHeight() - h; }
	if(angle < 0.1f && angle > -0.1f){
		angle = 0.2f;
	}

	if(-1 == speedTimer){ speedTimer = clock(); }
	if(clock() - speedTimer >= CLOCKS_PER_SEC * 5){ 
		speed ++;
		speedTimer = clock(); 
	}
	animator->update();
}

void PongBall::runCaughtP1State(){
	const Uint8* keys = GameEngine::getKeyState();
	speed = 0;
	x = p1->getX() + p1->getWidth() + (w / 2);
	y = p1->getY() + (p1->getHeight() / 2) - (h / 2);
	if(keys[GameEngine::SPACE_KEY] || GameEngine::GAMEPAD1_A){
		speed = tempSpeed;
		currentState = BOUNCE_STATE;
	}
	animator->setAnimation("ice");
	animator->update();
}

void PongBall::runCaughtP2State(){
	const Uint8* keys = GameEngine::getKeyState();
	speed = 0;
	x = p2->getX() - w - (w / 2);
	y = p2->getY() + (p2->getHeight() / 2) - (h / 2);
	if(keys[GameEngine::SPACE_KEY] || GameEngine::GAMEPAD2_A){
		speed = tempSpeed;
		currentState = BOUNCE_STATE;
	}
	animator->setAnimation("fire");
	animator->update();
}

void PongBall::draw(){
	//GameEngine::setRotationRad(angle);
	GameEngine::drawImage(animator->getCurrentImage(), x, y, w, h);
	GameEngine::setColor(1.0f, 0.0f, 0.0f);
	GameEngine::drawRect(cbox->getX(), cbox->getY(), cbox->getWidth(), cbox->getHeight());
	//GameEngine::setRotationRad(0);
}

void PongBall::checkCollision(GameObject* o){
	cbox->checkCollision(*o);

	if(cbox->isColliding()){
		int cx = x + (w / 2);
		int cy = y + (h / 2);
		int ocx = o->getX() + (o->getWidth() / 2);
		int ocy = o->getY() + (o->getHeight() / 2);
	
		if(currentState == BOUNCE_STATE){
			if(o->getTag().compare("paddle1") == 0){
				if(x < o->getX() && y > o->getY() && (y + h < o->getY() + o->getHeight())){ 
					tempSpeed = speed;
					currentState = CAUGHT_P1_STATE;
				}else{
					angle = (PI / 2) - (atan2((cy - ocy), (cx - ocx)));
					GameEngine::playSoundEffect("tock");
					animator->setAnimation("ice");
				}
			}else if(o->getTag().compare("paddle2") == 0){
				if((x + w > o->getX() + o->getWidth()) && y > o->getY() && (y + h < o->getY() + o->getHeight())){ 
					tempSpeed = speed;
					currentState = CAUGHT_P2_STATE;
				}else{
					angle = (PI / 2) - (atan2((cy - ocy), (cx - ocx)));
					GameEngine::playSoundEffect("tock");
					animator->setAnimation("fire");
				}
			}else if(o->getTag().compare("base") == 0){ 
				PongBase *b = static_cast<PongBase*>(o);			
				angle = (2 * PI) - angle;
				x += (speed * sin(angle));
				y += (speed * cos(angle));
				b->registerHit();
				b = NULL;
				GameEngine::playSoundEffect("smash");
			}
		}
	}
}

void PongBall::reset(int x, int y){
	this->x = x;
	this->y = y;

	speed = SPEED;
}

void PongBall::init(){
	currentState = GAME_START_STATE;
	tag = "ball";
	cbox = new CollisionBox(x, y, w, h);
	angle = PI / 4;
	speed = SPEED;
	
	speedTimer = -1;

	nextX = x;
	nextY = y;

	srand (time(NULL));	

	animator = new Animator();
	fireA = new Animation(10);
	iceA = new Animation(10);
	fireA->loadImage("../LinuxGameEngine/res/fireball1.png", true);
	fireA->loadImage("../LinuxGameEngine/res/fireball2.png", true);

	iceA->loadImage("../LinuxGameEngine/res/iceball1.png", true);	
	iceA->loadImage("../LinuxGameEngine/res/iceball2.png", true);	

	animator->loadAnimation("fire", fireA);
	animator->loadAnimation("ice", iceA);
	GameEngine::loadSoundEffect("bonk", "../LinuxGameEngine/res/sounds/sound.wav");
	GameEngine::loadSoundEffect("tock", "../LinuxGameEngine/res/sounds/tock.wav");
	GameEngine::loadSoundEffect("smash", "../LinuxGameEngine/res/sounds/base_hit.wav");
}
