#version 330 core
out vec4 color;

in vec2 texCoordinates;

uniform sampler2D text;

void main()
{    
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoordinates).r);
    color = vec4(1.0, 0.0, 1.0, 1.0) * sampled;
}  
