#pragma once

#include <math.h>
#include "GameEngine/Shader.h"
#include "GameEngine/GameWindow.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer{
public:
	Renderer(GameWindow* win);
	virtual ~Renderer();

	void setColor(int r, int g, int b);
	void setColor(float r, float g, float b);

	void fillRect(int x, int y, int w, int h);
	void fillOval(int x, int y, int w, int h);
	void drawImage(int x, int y, int w, int h);

private:
	GLuint sqVAO;
	GLuint sqVBO;
	GLuint crVAO;
	GLuint crVBO;

	GLuint texAttrib;	
	GLuint texture;

	GLuint transUniform;
	GLuint colorUniform;

	GLuint texTransUniform;

	Shader* shader;
	Shader* texShader;
	GameWindow* window;

	glm::mat4 transform;

	static GLfloat crVerts[722];
	static GLuint crElmts[360 * 3];

	void initCrVerts();
	void calcScale(int w, int h);
	void calcTranslate(int x, int y);

	float r;
	float g;
	float b;
};
