#pragma once

#include <math.h>
#include <ctime>
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameObject.h"
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
	private:
		CollisionBox* cbox;

		clock_t speedTimer;		

		int nextX;
		int nextY;			
		
		int speed;
		float angle;		

		void init();

		Animation* a1;
		Animation* a2;
		Animator* animator;
};
