#include "GameEngine/Renderer.h"	

const double PI = 3.1415926535897;

const GLfloat sqVerts[16] = { 
					0.0f, 0.0f, 0.0f, 1.0f,
					0.0f, 1.0f,	0.0f, 0.0f,
			   		1.0f, 1.0f, 1.0f, 0.0f,
			   		1.0f, 0.0f,	1.0f, 1.0f
			    };

const GLuint sqElmts[6] = {0, 1, 2, 2, 3, 0};
const GLuint boxElmts[4] = { 0, 1, 2, 3 };

GLfloat Renderer::crVerts[722];

GLuint Renderer::crElmts[NUM_ELMS];

Renderer::Renderer(GameWindow* win){
	this->strokeWidth = 1;

	this->r = 0.5;
	this->g = 0.5;
	this->b = 0.5;		

	this->window = win;

	textRenderer = new TextRenderer();
	textRenderer->loadFont("asimov", "../LinuxGameEngine/res/fonts/Asimov.otf");

	initShaders();

	initCrVerts();
	
	initRectBuffer();
	initEllipseBuffer();

	loadUniforms();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer(){
	glDeleteVertexArrays(1, &sqVAO);
	glDeleteBuffers(1, &sqVBO);

	glDeleteVertexArrays(1, &crVAO);
	glDeleteBuffers(1, &crVBO);

	delete shader;
	delete textureShader;
	delete textRenderer;

	for(std::map<std::string, Texture*>::iterator it = textures.begin();
		it != textures.end(); it++){
		delete it->second;
	}
}

void Renderer::loadUniforms(){
	transUniform = glGetUniformLocation(shader->getProgram(), "transformation");
	colorUniform = glGetUniformLocation(shader->getProgram(), "inColor");
	texTransUniform = glGetUniformLocation(textureShader->getProgram(), "transformation");
}

void Renderer::initShaders(){
	shader = new Shader("../LinuxGameEngine/shaders/basic_vertex.vs", 
	"../LinuxGameEngine/shaders/basic_fragment.fs");

	textureShader = new Shader("../LinuxGameEngine/shaders/basic_tex_vertex.vs", 
	"../LinuxGameEngine/shaders/basic_tex_fragment.fs");
}

void Renderer::initRectBuffer(){
	glGenVertexArrays(1, &sqVAO);
	glGenBuffers(1, &sqVBO);
	
	glBindVertexArray(sqVAO);

	glBindBuffer(GL_ARRAY_BUFFER, sqVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sqVerts), sqVerts, GL_STATIC_DRAW);
	
	texAttrib = glGetAttribLocation(textureShader->getProgram(), "texCoord");
    glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sqElmts), sqElmts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::initEllipseBuffer(){
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

	shader->useProgram();

	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform4f(colorUniform, r, g, b, 1.0f);

	glBindVertexArray(sqVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

void Renderer::drawRect(int x, int y, int w, int h){
	transform = glm::mat4();
	calcTranslate(x, y);
	calcScale(w, h);	

	shader->useProgram();

	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform4f(colorUniform, r, g, b, 1.0f);

	glBindVertexArray(sqVAO);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(strokeWidth);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	
	glBindVertexArray(0);
}

void Renderer::fillOval(int x, int y, int w, int h){
	transform = glm::mat4();
	calcTranslate(x + (w / 2), y + (h / 2));
	calcScale(w / 2, h / 2);
	
	shader->useProgram();

	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform4f(colorUniform, r, g, b, 1.0f);

	glBindVertexArray(crVAO);
	glDrawElements(GL_TRIANGLES, NUM_ELMS, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::drawImage(std::string imageName, int x, int y, int w, int h){
	transform = glm::mat4();
	calcTranslate(x, y);
	calcRotation();
	calcScale(w, h);
	
	
	textureShader->useProgram();
	
	if(textures[imageName]->isTransparent()){
		glEnable(GL_BLEND);
	}else{
		glDisable(GL_BLEND);
	}

	glBindTexture(GL_TEXTURE_2D, textures[imageName]->getID());
	glUniformMatrix4fv(texTransUniform, 1, GL_FALSE, glm::value_ptr(transform));

	glBindVertexArray(sqVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Renderer::loadImage(std::string textureName, std::string textureLoc, bool hasTransparency){
	textures[textureName] = new Texture(textureLoc, hasTransparency);
}

void Renderer::drawText(std::string text, int x, int y, float scale){
	textRenderer->renderText(text, x, y, scale, glm::vec3(r, g, b));
}

void Renderer::setDimensions(float w, float h){
	textRenderer->setDimensions(w, h);
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

	crElmts[ectr++] = 0;
	crElmts[ectr++] = 360;
	crElmts[ectr++] = 1;
}

void Renderer::calcScale(int w, int h){
	float sx = ((float)w / 900.0f * (float)gameWidth) / window->getWindowWidth();
	float sy = ((float)h / 600.0f * (float)gameHeight) / window->getWindowHeight();
	//float scalex = (float)w / (float)gameWidth * 2;
	//float scaley = (float)h / (float)gameHeight * 2;

	float scalex = sx * 2;
	float scaley = sy * 2;

	transform = glm::scale(transform, glm::vec3(scalex, scaley, 0.0));
}

void Renderer::calcTranslate(int x, int y){
	float nx = ((float)x / 900.0f * (float)gameWidth) / (float)window->getWindowWidth();
	float ny = ((float)y / 600.0f * (float)gameHeight) / (float)window->getWindowHeight();
	//float newX = (((float)x / (float)gameWidth) * 2.0) - 1.0;
	//float newY = (((float)y / (float)gameHeight) * 2.0) - 1.0;

	float newX = (nx * 2) - 1.0f;
	float newY = (ny * 2) - 1.0f;

	transform = glm::translate(transform, glm::vec3(newX, newY, 0.0));
}

void Renderer::calcRotation(){
	transform = glm::rotate(transform, rotation, glm::vec3(0, 0, 1));
}

void Renderer::loadFont(std::string fontName, std::string fontLoc){
	textRenderer->loadFont(fontName, fontLoc);
}

void Renderer::setFont(std::string font){
	textRenderer->setFont(font);
}

