#include "GameEngine/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const double PI = 3.1415926535897;

const GLfloat sqVerts[16] = { 
					0.0f, 0.0f, 0.0f, 1.0f,
					0.0f, 1.0f,	0.0f, 0.0f,
			   		1.0f, 1.0f, 1.0f, 0.0f,
			   		1.0f, 0.0f,	1.0f, 1.0f
			    };

const GLuint sqElmts[6] = {0, 1, 2, 2, 3, 0};

GLfloat Renderer::crVerts[722];
GLuint Renderer::crElmts[360 * 3];

Renderer::Renderer(GameWindow* win){
	this->r = 0.5;
	this->g = 0.5;
	this->b = 0.5;		

	initCrVerts();

	shader = new Shader("../LinuxGameEngine/shaders/basic_vertex.vs", 
	"../LinuxGameEngine/shaders/basic_fragment.fs");

	texShader = new Shader("../LinuxGameEngine/shaders/basic_tex_vertex.vs", 
	"../LinuxGameEngine/shaders/basic_tex_fragment.fs");

	this->window = win;

	//SQUARE VAO & VBO

	glGenVertexArrays(1, &sqVAO);
	glGenBuffers(1, &sqVBO);
	
	glBindVertexArray(sqVAO);

	glBindBuffer(GL_ARRAY_BUFFER, sqVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sqVerts), sqVerts, GL_STATIC_DRAW);
	
	texAttrib = glGetAttribLocation(texShader->getProgram(), "texCoord");
    glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sqElmts), sqElmts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//CIRCLE VAO & VBO

	glGenVertexArrays(1, &crVAO);
	glGenBuffers(1, &crVBO);
	
	glBindVertexArray(crVAO);

	glBindBuffer(GL_ARRAY_BUFFER, crVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crVerts), crVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);  

	GLuint cebo;
    glGenBuffers(1, &cebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(crElmts), crElmts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//TEXTURE
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	int w;
	int h;
	int comp;
	GLubyte* image = stbi_load("../LinuxGameEngine/res/dice.png", &w, &h, &comp, STBI_rgb_alpha);

	//float pixels[] = {
    //	1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
   	//	0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f
	//};

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	

	//UNIFORMS
	transUniform = glGetUniformLocation(shader->getProgram(), "transformation");
	colorUniform = glGetUniformLocation(shader->getProgram(), "inColor");
	texTransUniform = glGetUniformLocation(texShader->getProgram(), "transformation");
}

Renderer::~Renderer(){
	glDeleteTextures(1, &texture);

	glDeleteVertexArrays(1, &sqVAO);
	glDeleteBuffers(1, &sqVBO);

	glDeleteVertexArrays(1, &crVAO);
	glDeleteBuffers(1, &crVBO);

	delete shader;
	delete texShader;
}

void Renderer::setColor(int r, int g, int b){
	this->r = (float)r / 255.0f;
	this->g = (float)g / 255.0f;
	this->b = (float)b / 255.0f;
}

void Renderer::setColor(float r, float g, float b){
	this->r = r;
	this->g = g;
	this->b = b;
}

void Renderer::fillRect(int x, int y, int w, int h){
	transform = glm::mat4();
	calcTranslate(x, y);
	calcScale(w, h);

	glUseProgram(shader->getProgram());

	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform4f(colorUniform, r, g, b, 1.0f);

	glBindVertexArray(sqVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::fillOval(int x, int y, int w, int h){
	transform = glm::mat4();
	calcTranslate(x + (w / 2), y + (h / 2));
	calcScale(w / 2, h / 2);

	glUseProgram(shader->getProgram());

	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform4f(colorUniform, r, g, b, 1.0f);

	
	glBindVertexArray(crVAO);
	glDrawElements(GL_TRIANGLES, 360 * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::drawImage(int x, int y, int w, int h){
	transform = glm::mat4();
	calcTranslate(x, y);
	calcScale(w, h);

	glUseProgram(texShader->getProgram());
	
	glUniformMatrix4fv(texTransUniform, 1, GL_FALSE, glm::value_ptr(transform));
	//glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(sqVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Renderer::initCrVerts(){
	int ctr = 2;
	int ectr = 0;
	
	crVerts[0] = 0.0f;
	crVerts[1] = 0.0f;

	for(int i = 0; i < 360; i++){
		crVerts[ctr++] = (GLfloat)sin((PI * i) / 180.0f);
		crVerts[ctr++] = (GLfloat)cos((PI * i) / 180.0f);

		crElmts[ectr++] = 0;
		crElmts[ectr++] = i + 1;
		crElmts[ectr++] = i + 2;
	}
}

void Renderer::calcScale(int w, int h){
	float scalex = (float)w / (float)window->getWindowWidth() * 2;
	float scaley = (float)h / (float)window->getWindowHeight() * 2;
	transform = glm::scale(transform, glm::vec3(scalex, scaley, 0.0));
}

void Renderer::calcTranslate(int x, int y){
	float newX = (((float)x / (float)window->getWindowWidth()) * 2.0) - 1.0;
	float newY = (((float)y / (float)window->getWindowHeight()) * 2.0) - 1.0;

	transform = glm::translate(transform, glm::vec3(newX, newY, 0.0));
}

