#pragma once

#include "GameEngine/Shader.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer{
public:
	Renderer();
	virtual ~Renderer();

	void refresh();
	void setColor(int r, int g, int b);
	void setColor(float r, float g, float b);

	void fillRect(int x, int y, int w, int h);

private:
	GLuint VAO;
	GLuint VBO;	
	Shader* shader;
};
