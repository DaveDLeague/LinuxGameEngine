#include "GameEngine/Animation.h"

int Animation::animationCount = 0;

Animation::Animation(int f){
	fps = f;
	isPaused = false;
	currentFrame = 1;
	frameCount = 0;
	animationCount++;
	animCtr = animationCount;
	startTime = -1;
}

Animation::~Animation(){

}

void Animation::update(){
	if(isPaused){ return; }

	if(startTime == -1){ startTime = clock(); }
	if(clock() - startTime >= CLOCKS_PER_SEC / fps){
		currentFrame++;
		startTime = clock();
	}

	if(currentFrame > frameCount){ currentFrame = 1; }
	frameStream.str("");
	frameStream << "Animation#" << animCtr << "Frame#" << currentFrame;
	currentImageString = frameStream.str();
}

void Animation::loadImage(std::string file){
	frameStream.str("");
	frameStream << "Animation#" << animCtr << "Frame#" << ++frameCount;
	currentImageString = frameStream.str();
	GameEngine::loadImage(frameStream.str(), file, true);
}
