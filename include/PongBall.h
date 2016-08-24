#pragma once

#include "GameEngine/GameEngine.h"
#include "GameEngine/GameObject.h"
#include "GameEngine/CollisionBox.h"

class PongBall : public GameObject {
	public:
		PongBall(int x, int y, int w, int h);
		virtual ~PongBall();

		virtual void update();
		virtual void draw();

		void checkCollision(GameObject o);
	private:
		CollisionBox* cbox;
	
		int xspeed;
		int yspeed;

		void init();

};
