#pragma once

#include "GameEngine/GameObject.h"
#include "PongHUD.h"

class PongBase: public GameObject{
public:
	PongBase(int x, int y, int w, int h);
	virtual ~PongBase();
	virtual void draw();
	virtual void registerHit();
	
	void setHUD(PongHUD* h){ hud = h; }
	int getCurrentStatus(){ return currentStatus; }
	int getMaxStatus(){ return maxStatus; }
	void setCurrentStatus(int s);
	void setMaxStatus(int m);
	
protected:

	int maxStatus;
	int currentStatus;

	PongHUD* hud;

	void init();
private:
	
};
