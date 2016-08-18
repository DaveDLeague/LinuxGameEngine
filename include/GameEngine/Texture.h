#pragma once

#include <string>

#include "GL/glew.h"

class Texture{
public:
	Texture(std::string filename, bool hasTransparency);
	virtual ~Texture();
private:
};
