#pragma once

#include "GameEngine/GameObject.h"
#include "GameEngine/CollisionBox.h"

class PongBall : public GameObject {
	public:
		PongBall(int x, int y, int w, int h);
		PongBall(int x, int y, int w, int h, int r, int g, int b);
		PongBall(int x, int y, int w, int h, float r, float g, float b);
		virtual ~PongBall();

		virtual void update();
		virtual void draw(Renderer* r);

		void checkCollision(GameObject o);
	private:
		CollisionBox* cbox;
	
		int xspeed;
		int yspeed;

		void init();

};
