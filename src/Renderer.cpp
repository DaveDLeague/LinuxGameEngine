#include "GameEngine/Renderer.h"

const double PI = 3.1415926535897;

const GLfloat sqVerts[12] = { 
				0.0f, 0.0f,
				0.0f, 1.0f,
			   	1.0f, 1.0f,
			   	1.0f, 1.0f,
			   	1.0f, 0.0f,
			   	0.0f, 0.0f,
			    };

GLfloat Renderer::crVerts[2160];

Renderer::Renderer(GameWindow* win){
	initCrVerts();

	shader = new Shader("../LinuxGameEngine/shaders/basic_vertex.vs", 
	"../LinuxGameEngine/shaders/basic_fragment.fs");

	this->window = win;

	//SQUARE VAO & VBO

	glGenVertexArrays(1, &sqVAO);
	glGenBuffers(1, &sqVBO);
	
	glBindVertexArray(sqVAO);

	glBindBuffer(GL_ARRAY_BUFFER, sqVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sqVerts), sqVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//CIRCLE VAO & VBO

	glGenVertexArrays(1, &crVAO);
	glGenBuffers(1, &crVBO);
	
	glBindVertexArray(crVAO);

	glBindBuffer(GL_ARRAY_BUFFER, crVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crVerts), crVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

	transUniform = glGetUniformLocation(shader->getProgram(), "transformation");
}

Renderer::~Renderer(){
	glDeleteVertexArrays(1, &sqVAO);
	glDeleteBuffers(1, &sqVBO);

	glDeleteVertexArrays(1, &crVAO);
	glDeleteBuffers(1, &crVBO);

	delete shader;
}

void Renderer::setColor(int r, int g, int b){

}

void Renderer::setColor(float r, float g, float b){

}

void Renderer::fillRect(int x, int y, int w, int h){
	transform = glm::mat4();
	calcTranslate(x, y);
	calcScale(w, h);

	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(transform));

	glUseProgram(shader->getProgram());
	glBindVertexArray(sqVAO);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(sqVerts) / 2);
	glBindVertexArray(0);
}

void Renderer::fillOval(int x, int y, int w, int h){
	transform = glm::mat4();
	calcTranslate(x, y);
	calcScale(w, h);
	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(transform));

	glUseProgram(shader->getProgram());
	glBindVertexArray(crVAO);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(crVerts) / 2);
	glBindVertexArray(0);
}

void Renderer::initCrVerts(){
	int ctr = 0;
	for(int i = 0; i < 360; i++){
		
		crVerts[ctr++] = 0;
		crVerts[ctr++] = 0;

		crVerts[ctr++] = (GLfloat)sin((PI * i) / 180.0f);
		crVerts[ctr++] = (GLfloat)cos((PI * i) / 180.0f);
	
		crVerts[ctr++] = (GLfloat)sin((PI * (i + 1)) / 180.0f);
		crVerts[ctr++] = (GLfloat)cos((PI * (i + 1)) / 180.0f);
	}
}

void Renderer::calcScale(int w, int h){
	float scalex = (float)w / (float)window->getWindowWidth();
	float scaley = (float)h / (float)window->getWindowHeight();
	transform = glm::scale(transform, glm::vec3(scalex * 2, scaley * 2, 0.0));
}

void Renderer::calcTranslate(int x, int y){
	float newX = (((float)x / (float)window->getWindowWidth()) * 2.0) - 1.0;
	float newY = (((float)y / (float)window->getWindowHeight()) * 2.0) - 1.0;

	transform = glm::translate(transform, glm::vec3(newX, newY, 0.0));
}

