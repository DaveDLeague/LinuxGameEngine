#include "PongHUD.h"

PongHUD::PongHUD(){
	p1Meter = new StatusMeter(100, 575, 350, 25);
	p1Meter->invertMeter(true);
	p2Meter = new StatusMeter(450, 575, 350, 25);
}

PongHUD::~PongHUD(){
	delete p1Meter;
	delete p2Meter;
}

void PongHUD::update(){

}

void PongHUD::draw(){
	p1Meter->draw();
	p2Meter->draw();
}

void PongHUD::setP1MaxStatus(int m){
	p1Meter->setMaxStatus(m);
}

void PongHUD::setP1CurrentStatus(int c){
	p1Meter->setCurrentStatus(c);
}

void PongHUD::setP2MaxStatus(int m){
	p2Meter->setMaxStatus(m);
}

void PongHUD::setP2CurrentStatus(int c){
	p2Meter->setCurrentStatus(c);
}
