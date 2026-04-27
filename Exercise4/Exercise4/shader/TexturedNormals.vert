#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec2 vTexCoords;
layout(location = 4) in vec3 vTangent;

out vec3 fragColor;

uniform mat4 mvpMatrix;

/* TODO Add the normal sampler */

/* End TODO*/

void main()
{
	if((gl_VertexID & 1) == 1)
	{
		gl_Position = mvpMatrix * vec4(vPosition, 1);
	}
	else
	{
		gl_Position = mvpMatrix * vec4(vPosition, 1);

		/* TODO Calcualte the gl_position of the enpoint fo the normal */

		/* TODO END */
	}

	fragColor = vColor;
}

