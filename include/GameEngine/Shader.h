#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "GL/glew.h"

using namespace std;

class Shader {
public:
	Shader(string vertexFile, string fragmentFile);

	virtual ~Shader();

	GLuint getProgram() const {
		return program;
	}

	void useProgram();

private:

	GLuint program;
};

