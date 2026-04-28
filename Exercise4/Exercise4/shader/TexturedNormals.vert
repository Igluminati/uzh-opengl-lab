#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec2 vTexCoords;
layout(location = 4) in vec3 vTangent;

out vec3 fragColor;

uniform mat4 mvpMatrix;

/* TODO Add the normal sampler */

uniform sampler2D normalTex;

/* End TODO*/

void main()
{
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent - dot(vTangent, N) * N);
	vec3 B = cross(N, T);
	vec3 nm = texture(normalTex, vTexCoords).rgb * 2.0 - 1.0;
	vec3 nSample = normalize(T * nm.x + B * nm.y + N * nm.z);

	if((gl_VertexID & 1) == 1)
	{
		gl_Position = mvpMatrix * vec4(vPosition, 1);
	}
	else
	{
		/* TODO Calcualte the gl_position of the enpoint fo the normal */

		gl_Position = mvpMatrix * vec4(vPosition + 0.2 * nSample, 1.0);

		/* TODO END */
	}

	fragColor = vColor;
}
