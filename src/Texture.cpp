#include "GameEngine/Texture.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

Texture::Texture(std::string filename, bool hasTransparency){
	/*GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int w;
	int h;
	int comp;
	GLubyte* image = stbi_load("../LinuxGameEngine/res/dice.png", &w, &h, &comp, STBI_rgb_alpha);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
}

Texture::~Texture(){

}
