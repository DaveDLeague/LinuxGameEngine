#version 330

in vec2 position;
in vec2 texCoord;

uniform mat4 transformation;

out vec2 outTex;

void main()
{
	outTex = texCoord;
	gl_Position = transformation * vec4(position.x, position.y, 0.0, 1.0);
}
