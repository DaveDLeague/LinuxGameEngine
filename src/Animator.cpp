#include "GameEngine/Animator.h"

Animator::Animator(){
	currentAnimation = "";
	currentImage = "";
}

Animator::~Animator(){
	for(std::map<std::string, Animation*>::iterator it = animations.begin();
		it != animations.end(); it++){
		it->second = NULL;
	}
}

void Animator::update(){
	currentImage = animations[currentAnimation]->getCurrentImageString();
	animations[currentAnimation]->update();
}

void Animator::loadAnimation(std::string ref, Animation* ani){
	animations[ref] = ani;	
	currentAnimation = ref;
	currentImage = ani->getCurrentImageString();
}
