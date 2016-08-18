#pragma once

#include "GameEngine/GameObject.h"
#include "GameEngine/CollisionBox.h"

class PongPaddle : public GameObject {
	public:
		PongPaddle(int x, int y, int w, int h);
		virtual ~PongPaddle();

		virtual void update();
		virtual void draw();
	private:
		CollisionBox* cbox;

		int speed;

		void init();

};
