#include "GameEngine/Renderer.h"

const GLfloat vertices[18] = { 
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
			   	1.0f, 1.0f, 0.0f,
			   	1.0f, 1.0f, 0.0f,
			   	1.0f, 0.0f, 0.0f,
			   	0.0f, 0.0f, 0.0f,
			    };

Renderer::Renderer(){
	shader = new Shader("/home/dave/Desktop/linuxgameengine/shaders/basic_vertex.vs", 
	"/home/dave/Desktop/linuxgameengine/shaders/basic_fragment.fs");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
	GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
			(GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

Renderer::~Renderer(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete shader;
}

int xx = 100;
int yy = 100;
int w = 200;
int h = 200;
int width = 1280;
int height = 920;
int speed = 1;

void Renderer::refresh(){
	xx += speed;

	if(xx >= width || xx <= 0){
		speed = -speed;
	}	

	float newX = (((float)xx / (float)width) * 2.0) - 1.0;
	float newY = (((float)yy / (float)height) * 2.0) - 1.0;

	float scalex = (float)w / (float)width;
	float scaley = (float)h / (float)height;

	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(newX, newY, 0.0));
	transform = glm::scale(transform, glm::vec3(scalex, scaley, 0.0));

	GLint uniTrans = glGetUniformLocation(shader->getProgram(),
			"transformation");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(transform));

	glUseProgram(shader->getProgram());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::setColor(int r, int g, int b){

}

void Renderer::setColor(float r, float g, float b){

}

void Renderer::fillRect(int x, int y, int w, int h){

}
