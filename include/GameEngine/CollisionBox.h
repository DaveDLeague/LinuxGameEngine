#pragma once

#include "GameEngine/GameObject.h"

class CollisionBox: public GameObject{
	public:
		CollisionBox(int x, int y, int w, int h);
		CollisionBox(int x, int y, int w, int h, int r, int g, int b);
		CollisionBox(int x, int y, int w, int h, float r, float g, float b);

		virtual void update();
		virtual void update(int x, int y, int w, int h);
		virtual void draw(Renderer* r);
		virtual void checkCollision(GameObject o);
	
		bool isColliding(){ return collision; }

	private:
		bool collision;

		virtual void init();

};
