#include "GameEngine/Game.h"
#include <iostream>
Game::Game(){

}

Game::Game(int w, int h, std::string t){
	this->width = w;
	this->height = h;
	this->title = t;
}

Game::~Game(){

}

void Game::update(){

}
