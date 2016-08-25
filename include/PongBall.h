#pragma once

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameObject.h"
#include "GameEngine/CollisionBox.h"

class PongBall : public GameObject {
	public:
		PongBall(int x, int y, int w, int h);
		virtual ~PongBall();

		virtual void update();
		virtual void draw();

		void checkCollision(GameObject* o);
	private:
		CollisionBox* cbox;
			
		int nextX;
		int nextY;			
			
		int speed;
		float angle;		

		void init();

};
