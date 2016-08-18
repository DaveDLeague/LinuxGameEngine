#pragma once

#include "GameEngine/GameEngine.h"
#include "GameEngine/Renderer.h"

class GameObject{
public:
	GameObject(int x, int y, int w, int h);

	virtual ~GameObject();
	
	virtual void update();
	virtual void draw();
	
	int getX(){ return x; }
	int getY(){ return y; }
	int getWidth(){ return w; }
	int getHeight(){ return h; }	 
	

protected:
	int x;
	int y;
	int w;
	int h;

private:
	virtual void init(int x, int y, int w, int h);
};
