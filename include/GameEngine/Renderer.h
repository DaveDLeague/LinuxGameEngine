#pragma once

#include <string>
#include <math.h>
#include "GameEngine/Shader.h"
#include "GameEngine/GameWindow.h"
#include "GameEngine/TextRenderer.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define NUM_ELMS 361 * 3

class Renderer{
public:
	Renderer(GameWindow* win);
	virtual ~Renderer();

	void setColor(int r, int g, int b);
	void setColor(float r, float g, float b);

	void fillRect(int x, int y, int w, int h);
	void drawRect(int x, int y, int w, int h);
	void fillOval(int x, int y, int w, int h);
	void drawImage(int x, int y, int w, int h);
	void drawText(std::string text, int x, int y);

	void setStrokeWidth(int w) { strokeWidth = w; }

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
	Shader* textureShader;

	GameWindow* window;
	TextRenderer* textRenderer;

	glm::mat4 transform;

	static GLfloat crVerts[722];
	static GLuint crElmts[NUM_ELMS];

	void initCrVerts();
	void calcScale(int w, int h);
	void calcTranslate(int x, int y);
	void loadUniforms();
	void initShaders();
	void initRectBuffer();
	void initEllipseBuffer();

	int strokeWidth;
	
	float r;
	float g;
	float b;
};
