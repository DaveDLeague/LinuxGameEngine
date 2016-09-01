#pragma once

#include <string>

#include "GL/glew.h"

class Texture{
public:
	Texture(std::string filename, bool hasTransparency);
	virtual ~Texture();
	
	GLuint getID(){ return textureID; }
	bool isTransparent(){ return transparent; }
private:
	GLuint textureID;
	bool transparent;
};
