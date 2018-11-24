#version 330 core
// in
layout (location=0) in vec3 position;

// uniform values
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
	gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0f);
}