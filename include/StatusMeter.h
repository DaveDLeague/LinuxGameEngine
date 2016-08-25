#pragma once

#include "GameEngine/GameObject.h"

class StatusMeter: public GameObject{
public:
	StatusMeter(int x, int y, int w, int h);
	virtual ~StatusMeter();
	virtual void draw();
	
	void setMaxStatus(int max){ maxStatus = max; }
	void setCurrentStatus(int sts){ currentStatus = sts; }
	void incrementCurrentStatus(int amt){ 
		currentStatus += amt; 
		if(currentStatus < 0) { 
			currentStatus = 0; 
		}else if(currentStatus > maxStatus){ 
			currentStatus = maxStatus; 
		}	
	}
private:
	int maxStatus;
	int currentStatus;

	void init();
};

