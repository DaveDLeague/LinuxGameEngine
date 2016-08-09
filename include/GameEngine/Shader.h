/*
 * Shader.h
 *
 *  Created on: Aug 4, 2016
 *      Author: dave
 */

#ifndef SHADER_H_
#define SHADER_H_

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

private:

	GLuint program;
};

#endif /* SHADER_H_ */
