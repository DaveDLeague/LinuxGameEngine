#pragma once

#include "GameEngine/GameObject.h"
#include "GameEngine/CollisionBox.h"

class PongPaddle : public GameObject {
	public:
		PongPaddle(int x, int y, int w, int h);
		PongPaddle(int x, int y, int w, int h, int r, int g, int b);
		PongPaddle(int x, int y, int w, int h, float r, float g, float b);
		virtual ~PongPaddle();

		virtual void update();
		virtual void draw(Renderer* r);
	private:
		CollisionBox* cbox;

		int speed;

		void init();

};
