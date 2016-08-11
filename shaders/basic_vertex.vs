#version 330

layout (location = 0) in vec2 position;

uniform mat4 transformation;
uniform vec4 inColor;

out vec4 outColor;

void main()
{
	outColor = inColor;
	gl_Position = transformation * vec4(position.x, position.y, 0.0, 1.0);
}
