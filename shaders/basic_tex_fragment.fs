#version 330

out vec4 color;

in vec2 outTex;

uniform sampler2D tex;

void main()
{
	color = texture(tex, outTex);
}
