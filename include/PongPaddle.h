#pragma once

#include "GameEngine/GameObject.h"

class PongPaddle : public GameObject {
	public:
		PongPaddle(int x, int y, int w, int h);
		PongPaddle(int x, int y, int w, int h, int r, int g, int b);
		PongPaddle(int x, int y, int w, int h, float r, float g, float b);

		virtual void update();
		virtual void draw(Renderer* r);
	private:

		int speed;

		void init();

};
