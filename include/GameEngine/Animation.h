#pragma once

#include <string>
#include <sstream>
#include <ctime>
#include "GameEngine/GameEngine.h"

class Animation{
public:
	Animation(int f = 24);
	virtual ~Animation();

	void update();
	void loadImage(std::string file, bool t);
	void setFPS(int f){ fps = f; }
	void reset(){ currentFrame = 1; }
	void setCurrentFrame(int f){
		if(f < 1){ f = 1; }
		else if(f > frameCount){ f = frameCount; }
		currentFrame = f;
	}
	void pause(bool t){ isPaused = t; }

	std::string getCurrentImageString(){ return currentImageString; }
private:
	static int animationCount;

	int animCtr;
	bool isPaused;
	int currentFrame;
	int frameCount;	
	int fps;
	long startTime;

	std::string currentImageString;
	std::stringstream frameStream;
};
