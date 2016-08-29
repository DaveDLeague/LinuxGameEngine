#pragma once

#include <string>
#include <map>
#include "GameEngine/Animation.h"

class Animator{
public:
	Animator();
	virtual ~Animator();
	
	void update();
	void loadAnimation(std::string ref, Animation*);

	void setAnimation(std::string anim){ currentAnimation = anim; } 
	std::string getCurrentImage(){ return currentImage; }
private:
	std::string currentAnimation;
	std::string currentImage;

	map<std::string, Animation*> animations;
};
