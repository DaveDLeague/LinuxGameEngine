#pragma once

#include <math.h>
#include <ctime>
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameObject.h"
#include "PongPaddle.h"
#include "GameEngine/CollisionBox.h"
#include "GameEngine/Animator.h"

class PongBall : public GameObject {
	public:
		PongBall(int x, int y, int w, int h);
		virtual ~PongBall();

		virtual void update();
		virtual void draw();

		void reset(int x, int y);
		void checkCollision(GameObject* o);
		void setAngle(float a){ angle = a; }
		void setPaddles(PongPaddle* pp1, PongPaddle* pp2){
			p1 = pp1;
			p2 = pp2;
		}

		void setState(int state){ currentState = state; }
		enum states { 
				      GAME_START_STATE, 
					  BOUNCE_STATE,
					  CAUGHT_P1_STATE,
					  CAUGHT_P2_STATE
					 };
	private:
		
		CollisionBox* cbox;

		clock_t speedTimer;		

		int nextX;
		int nextY;			
		
		int currentState;
		int tempSpeed;
		int speed;
		float angle;		

		void init();

		Animation* fireA;
		Animation* iceA;
		Animator* animator;

		PongPaddle* p1;
		PongPaddle* p2;

		void runGameStartState();
		void runBounceState();
		void runCaughtP1State();
		void runCaughtP2State();
		
};
