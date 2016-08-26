#pragma once

#include "GameEngine/GameObject.h"

class StatusMeter: public GameObject{
public:
	StatusMeter(int x, int y, int w, int h);
	virtual ~StatusMeter();
	virtual void draw();
	
	void setMaxStatus(int max){ 
		if(max < 0) { max = 0; }		
		maxStatus = max; 
	}
	void setCurrentStatus(int sts){ 
		if(sts < 0) { 
			sts = 0; 
		}else if(sts > maxStatus){ 
			sts = maxStatus; 
		}	
		currentStatus = sts; 
	}
	void incrementCurrentStatus(int amt){ 
		currentStatus += amt; 
		if(currentStatus < 0) { 
			currentStatus = 0; 
		}else if(currentStatus > maxStatus){ 
			currentStatus = maxStatus; 
		}	
	}
	void invertMeter(bool i){ inverted = i; }
private:
	bool inverted;
	int maxStatus;
	int currentStatus;

	void init();
};

