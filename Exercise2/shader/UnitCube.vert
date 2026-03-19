#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

out vec3 objectColor;

uniform mat4 mvpMatrix;

void main()
{
	gl_Position = mvpMatrix * vec4(vPosition, 1);
	objectColor = vColor;
}

