
#version 330 core
in vec4 vertex; 

out vec2 texCoordinates;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
	texCoordinates = vertex.zw;
}
