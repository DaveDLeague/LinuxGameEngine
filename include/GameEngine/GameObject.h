#pragma once

#include <string>
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
	void setX(int nx){ x = nx; }
	void setY(int ny){ y = ny; }
	void setWidth(int nw){ w = nw; }
	void setHeight(int nh){ h = nh; }	 
	
	std::string getTag(){ return tag; }
	void setTag(std::string t){ tag = t; }

protected:
	int x;
	int y;
	int w;
	int h;
	
	std::string tag;
private:
	virtual void init(int x, int y, int w, int h);
};
