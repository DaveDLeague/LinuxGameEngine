#pragma once

#include <string>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameEngine/Shader.h"

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    long Advance;    // Horizontal offset to advance to next glyph
};

class TextRenderer{
	public:
		TextRenderer();
		virtual ~TextRenderer();

		void renderText(std::string text, int x, int y, int size);
		
private:
    GLuint VAO;
	GLuint VBO;

	std::map<GLchar, Character> characters;

	Shader* shader;

	void initBuffer();
};
