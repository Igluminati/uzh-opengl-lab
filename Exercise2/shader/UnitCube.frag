#version 410 core

in vec3 objectColor;
in vec3 worldPos;

out vec3 color;

void main()
{
	color = objectColor;
}

